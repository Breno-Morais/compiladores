#include "asm_handlers.h"
#include "asm_utils.h" // For symbolToAsm, getAsmDestination
#include <stdexcept> // For runtime_error

// --- Arithmetic Handlers ---
void handle_BinOp(std::ostringstream& oss, TAC* code, const std::string& instruction) {
    // Handle op1 (Load into %eax)
    bool op1_already_in_eax =  (code->prev && 
                                reusableResEax.count(code->prev->type) && 
                                code->prev->res == code->op1);

    if (!op1_already_in_eax) {
        // If not, we must load it.
        oss << "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n";
    }

    // Handle op2 (Load into %edx)
    oss << "\tmovl\t" << symbolToAsm(code->op2) << ", %edx\n";

    oss << "\t" << instruction << "\t%edx, %eax\n";

    oss << "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

void handle_Mul(std::ostringstream& oss, TAC* code) {
    if (code->op1->symType == SymbolType::Integer && code->op2->symType == SymbolType::Integer) {
        oss << "\tmovl\t$" << (std::stoi(code->op1->content) * std::stoi(code->op2->content)) 
            <<  ", %eax\n"
                "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
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
    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %ecx\n"
            "\tcltd\n"
            "\tidivl\t%ecx\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

void handle_Mod(std::ostringstream& oss, TAC* code) {
    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\tmovl\t" << symbolToAsm(code->op2) << ", %esi\n"
            "\tcltd\n"
            "\tidivl\t%esi\n"
            "\tmovl\t%edx, %ecx\n"
            "\tmovl\t%ecx, %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

void handle_Shift(std::ostringstream& oss, TAC* code, bool toLeft) {
    oss << "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
           "\t" << (toLeft ? "sall" : "sarl") << "\t$" << code->op2->content << ", %eax\n"
           "\tmovl\t%eax, " << getAsmDestination(code->res) << "\n";
}

// --- Logic/Comparison Handlers ---
void handle_Cmp(std::ostringstream& oss, TAC* code, const std::string& set_instruction) {
    oss <<  "\tmovl\t" << symbolToAsm(code->op2) << ", %eax\n"
            "\tcmpl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\t" << set_instruction << "\t%al\n"
            "\tmovzbl\t%al, %eax\n"
            "\tmovl\t%eax, " << code->res->content << "(%rip)\n";
}

void handle_And(std::ostringstream& oss, TAC* code, int& LCCounter) {
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
    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tsete\t%al\n"
            "\tmovzbl\t%al, %eax\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

// --- Control Flow Handlers ---
void handle_Label(std::ostringstream& oss, TAC* code) {
    oss << code->res->content << ":\n";
}

void handle_Jump(std::ostringstream& oss, TAC* code) {
    oss << "\tjmp\t" << code->res->content << "\n";
}

void handle_IfZ(std::ostringstream& oss, TAC* code)  {
    oss <<  "\tmovl\t" << symbolToAsm(code->op1) << ", %eax\n"
            "\ttestl\t%eax, %eax\n"
            "\tjz\t" << code->res->content << "\n";
}

void handle_BeginFun(std::ostringstream& oss, TAC* code) {
    int stackSize = 0;
    int value = -4;
    std::vector<Symbol*> locals;
    if(code->res->params.size() > 0) {
        stackSize = code->res->params.size() * 4;

        for(size_t i = 0; i < code->res->params.size(); i++) {
            code->res->params[i]->content = std::to_string(value);
            value -= 4;

            locals.push_back(code->res->params[i]);
        }
    }

    int i;
    ASTNode* funct = code->res->value;

    if(funct) {
        for(i = 0; funct->children[i] && funct->children[i]->type != ASTNodeType::LocalVarDecList; i++);

        if(funct->children[i]) {
            for(ASTNode* node = funct->children[i]; node != nullptr; node = node->children[1]) {
                if(node->children[0] && node->children[0]->symbol) {
                    node->children[0]->symbol->content = std::to_string(value);
                    value -= 4;
                    stackSize += 4;

                    locals.push_back(node->children[0]->symbol);
                }
            }
        }
    }

    // Aligns it to 16
    stackSize = (stackSize + 15) & ~15;

    oss <<  "\t.text\n"
            "\t.globl\t" << code->res->content << "\n"
            "\t.type\t" << code->res->content << ", @function\n"
            << code->res->content << ":\n"
            "\tendbr64\n"
            "\tpushq\t%rbp\n"
            "\tmovq\t%rsp, %rbp\n";
    
    // Initialize stack
    if(stackSize > 0)
        oss << "\tsubq\t$" << std::to_string(stackSize) << ", %rsp\n";

    // Initialize all local variables
    for (size_t i = 0; i < locals.size(); i++) {
        if(locals[i]->symType == SymbolType::Local) {
            // TODO: The value should be different
            oss << "\tmovl\t$" << locals[i]->value->symbol->content << ", " << symbolToAsm(locals[i]) << "\n";
        } else {
            int index = code->res->getParamIndex(locals[i]);
            if(index >= 0)
                oss << "\tmovl\t" << argumentLoc[index] << ", " << symbolToAsm(locals[i]) << "\n";
        }
    }
    
}

void handle_EndFun(std::ostringstream& oss, TAC* code) {
    oss <<  "\tmovq\t%rbp, %rsp\n"
            "\tpopq\t%rbp\n"
            "\tret\n"
            "\t.size\t" << code->res->content << ", .-" << code->res->content << "\n";
}

void handle_Return(std::ostringstream& oss, TAC* code) {
    if(!(code->prev && code->prev->res == code->res))
        oss << "\tmovl\t" << symbolToAsm(code->res) << ", %eax\n"; 
}

void handle_Call(std::ostringstream& oss, TAC* code) {
    oss <<  "\tcall\t" << code->op1->content << "\n"
            "\tmovl\t%eax, " << symbolToAsm(code->res) << "\n";
}

void handle_Arg(std::ostringstream& oss, TAC* code) {    
    int index = code->res->getParamIndex(code->op2);
    if(index >= 0)
        oss << "\tmovl\t" << symbolToAsm(code->op1) << ", " << argumentLoc[index] << "\n";
}

// --- I/O and Move Handlers ---
void handle_Move(std::ostringstream& oss, TAC* code) {
    Symbol* src = nullptr;
    Symbol* dst = nullptr;
    int index = -1;

    switch (code->type) {
        case TACType::MOVE:
            src = code->op1;
            dst = code->res;
            index = -1;
            break;

        case TACType::MOVEVEC:
            src = code->op2;
            dst = code->res;
            
            if(memorySym.count(code->op1->symType)) {
                oss << "\tmovl\t" << code->op1->content << "(%rip), %eax\n" <<
                       "\tcltq\n" <<
                       "\tleaq\t0(,%rax,4), %rdx\n" <<
                       "\tleaq\t" << src->content << "(%rip), %rax\n";
            } else
                index = std::stoi(code->op1->content);

            break;

        case TACType::VECACCESS:
            src = code->op2;
            dst = code->res;
            
            if(memorySym.count(code->op1->symType)) {
                oss << "\tmovl\t" << code->op1->content << "(%rip), %eax\n" <<
                       "\tcltq\n" <<
                       "\tleaq\t0(,%rax,4), %rdx\n" <<
                       "\tleaq\t" << src->content << "(%rip), %rax\n";
            } else
                index = std::stoi(code->op1->content);

            break;
        
        default:
            break;
    }

    if(src == nullptr || dst == nullptr)
        throw std::runtime_error("Invalide move instruction.");

    if(memorySym.count(src->symType)) {
        oss << 
            "\tmovl\t" << symbolToAsm(src, index) << ", %eax\n"
            "\tmovl\t%eax, " << getAsmDestination(dst, index) << "\n";
    } else
        oss << "\tmovl\t" << symbolToAsm(src, index) << ", " << getAsmDestination(dst, index) << "\n";
}

void handle_Read(std::ostringstream& oss, TAC* code) {
    oss <<  "\tleaq\t" << symbolToAsm(code->res) << ", %rax\n"
            "\tmovq\t%rax, %rsi\n"
            "\tleaq\t._print_d(%rip), %rax\n"
            "\tmovq\t%rax, %rdi\n"
            "\tmovl\t$0, %eax\n"
            "\tcall\t__isoc99_scanf@PLT\n";
}

void handle_Print(std::ostringstream& oss, TAC* code, int& LCCounter) {
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