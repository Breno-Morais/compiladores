#include "asm_handlers.h"
#include "asm_utils.h" // For symbolToAsm, getAsmDestination
#include <stdexcept> // For runtime_error

static void print_OriginalTAC(std::ostringstream& oss, TAC* code) {
    oss << "\n# TAC " << code->type << "\n";
}

// --- Arithmetic Handlers ---
void handle_BinOp(std::ostringstream& oss, TAC* code, const std::string& instruction) {
    print_OriginalTAC(oss, code);

    // 1. Handle op1 (Load into %eax)
    // We check if the previous instruction's result is *our* op1.
    bool op1_already_in_eax = (code->prev && code->prev->res == code->op1);

    if (!op1_already_in_eax) {
        // If not, we must load it.
        oss << "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n";
    }

    // 2. Handle op2 (Load into %edx)
    // No optimization for op2, just load it.
    oss << "\tmovl\t" << symbolToAsm(code->op2) << ", %edx\n";

    // 3. Perform the operation
    oss << "\t" << instruction << "\t%edx, %eax\n"; // e.g., "addl %edx, %eax"

    // 4. Handle the result (Store from %eax)
    // We check if the *next* instruction *uses* our result as op1.
    bool res_used_by_next = (code->next && 
                             (code->next->op1 == code->res || 
                              (code->next->type == TACType::RET && code->next->res == code->res)));

    if (!res_used_by_next) {
        // If not used immediately, we must store it back to memory.
        oss << "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
    }
}

void handle_Mul(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    // Your constant-folding optimization is good.
    if (code->op1->symType == SymbolType::Integer && code->op2->symType == SymbolType::Integer) {
        oss << "\tmovl\t$" << (std::stoi(code->op1->content) * std::stoi(code->op2->content)) 
            << ", " << getAsmDestination(code->res) << "\n";
    } 
    // Case 1: op1 is constant
    else if (code->op1->symType == SymbolType::Integer) {
        oss << "\tmovl\t" << symbolToAsm(code->op2) << ", %eax\n"
            "\timull\t" << symbolToAsm(code->op1) << ", %eax, %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
    }
    // Case 2: op2 is constant (imull is commutative)
    else if (code->op2->symType == SymbolType::Integer) {
        oss << "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\timull\t" << symbolToAsm(code->op2) << ", %eax, %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
    }
    // Case 3: Neither is constant
    else {
        oss << "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %edx\n"
            "\timull\t%edx, %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
    }
}

void handle_Div(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %ecx\n"
            "\tcltd\n"
            "\tidivl\t%ecx\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

void handle_Mod(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %esi\n"
            "\tcltd\n"
            "\tidivl\t%esi\n"
            "\tmovl\t%edx, %ecx\n"
            "\tmovl\t%ecx, %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

// --- Logic/Comparison Handlers ---
void handle_Cmp(std::ostringstream& oss, TAC* code, const std::string& set_instruction) {
    print_OriginalTAC(oss, code);

    oss <<  "\tmovl\t" << symbolToAsm(code->op2) << ", %eax\n"
            "\tcmpl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\t" << set_instruction << "\t%al\n"
            "\tmovzbl\t%al, %eax\n"
            "\tmovl\t%eax, " << code->res->content << "(%rip)\n";
}

void handle_And(std::ostringstream& oss, TAC* code, int& LCCounter) {
    print_OriginalTAC(oss, code);

    std::string labelPrint1 = ".L" + std::to_string(LCCounter);
    LCCounter++;
    std::string labelPrint2 = ".L" + std::to_string(LCCounter);
    LCCounter++;

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tje\t" << labelPrint1 << "\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tje\t" << labelPrint1 << "\n"
            "\tmovl\t$1, %eax\n"
            "\tjmp\t" << labelPrint2 << "\n" <<
            labelPrint1 << ":\n"
            "\tmovl\t$0, %eax\n" <<
            labelPrint2 << ":\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

void handle_Or(std::ostringstream& oss, TAC* code, int& LCCounter) {
    print_OriginalTAC(oss, code);

    std::string labelPrint1 = ".L" + std::to_string(LCCounter);
    LCCounter++;
    std::string labelPrint2 = ".L" + std::to_string(LCCounter);
    LCCounter++;
    std::string labelPrint3 = ".L" + std::to_string(LCCounter);
    LCCounter++;

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tjne\t" << labelPrint1 << "\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tje\t" << labelPrint2 << "\n"
            "" << labelPrint1 << ":\n"
            "\tmovl\t$1, %eax\n"
            "\tjmp\t" << labelPrint3 << "\n"
            "" << labelPrint2 << ":\n"
            "\tmovl\t$0, %eax\n"
            "" << labelPrint3 << ":\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

void handle_Not(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tsete\t%al\n"
            "\tmovzbl\t%al, %eax\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

// --- Control Flow Handlers ---
void handle_Label(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss << code->res->content << ":\n";
}

void handle_Jump(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss << "\tjmp\t" << code->res->content << "\n";
}

void handle_IfZ(std::ostringstream& oss, TAC* code)  {
    print_OriginalTAC(oss, code);

    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tjz\t" << code->res->content << "\n";
}

void handle_BeginFun(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\t.text\n"
            "\t.globl\t" << code->res->content << "\n"
            "\t.type\t" << code->res->content << ", @function\n"
            << code->res->content << ":\n"
            "\tendbr64\n"
            "\tpushq\t%rbp\n"
            "\tmovq\t%rsp, %rbp\n";
}

void handle_EndFun(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tpopq\t%rbp\n"
            "\tret\n"
            "\t.size\t" << code->res->content << ", .-" << code->res->content << "\n";
}

void handle_Return(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    if(!(code->prev && code->prev->res == code->res))
        oss << "\tmovl\t" << symbolToAsm(code->res) << ", %eax\n"; 
}

void handle_Call(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tcall\t" << code->op1->content << "\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

// --- I/O and Move Handlers ---
void handle_Move(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss << "\tmovl\t" << symbolToAsm(code->op1) << ", " << code->res->content << "(%rip)\n";
}

void handle_Read(std::ostringstream& oss, TAC* code) {
    print_OriginalTAC(oss, code);

    oss <<  "\tleaq\t" << symbolToAsm(code->res) << ", %rax\n"
            "\tmovq\t%rax, %rsi\n"
            "\tleaq\t._print_d(%rip), %rax\n"
            "\tmovq\t%rax, %rdi\n"
            "\tmovl\t$0, %eax\n"
            "\tcall\t__isoc99_scanf@PLT\n";
}

void handle_Print(std::ostringstream& oss, TAC* code, int& LCCounter) {
    print_OriginalTAC(oss, code);

    if(code->res->dataType == DataType::Bool) {
        std::string labelPrint1 = ".L" + std::to_string(LCCounter);
        LCCounter++;
        std::string labelPrint2 = ".L" + std::to_string(LCCounter);
        LCCounter++;

        oss <<  "\tmovzbl\t" << symbolToAsm(code->res) << ", %eax\n"
                "\ttestb\t%al, %al\n"
                "\tje\t" << labelPrint1 << "\n"
                "\tleaq\t.true(%rip), %rax\n"
                "\tjmp\t" << labelPrint2 << "\n"
                << labelPrint1 << ":\n"
                "\tleaq\t.false(%rip), %rax\n"
                << labelPrint2 << ":\n"
                "\tmovq\t%rax, %rdi\n"
                "\tcall\tprintf@PLT\n";

        return;
    }

    if(code->res->symType == SymbolType::String) {
        oss <<  "\tleaq\t" << symbolToAsm(code->res) << ", %rax\n"
                "\tmovq\t%rax, %rdi\n"
                "\tcall\tprintf@PLT\n";

        return;
    }

    oss << "\tmovl\t" << symbolToAsm(code->res) << ", %esi\n";

    oss << "\tleaq\t._print_";
    switch(code->res->dataType) {
        case DataType::Int:
            oss << "d";
            break;

        case DataType::Char:
            oss << "c";
            break;


        case DataType::Real:
            oss << "f";
            break;

        default:
            oss << "d";
            break;
    }

    oss << "(%rip), %rax\n";

    oss << "\tmovq\t%rax, %rdi\n"
            "\tmovl\t$0, %eax\n"
            "\tcall\tprintf@PLT\n";
}