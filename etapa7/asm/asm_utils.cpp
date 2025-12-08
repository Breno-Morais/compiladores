#include "asm_utils.h"

std::map<DataType, int> dataSizeTable = {
    {DataType::Int, 4},
    {DataType::Char, 1},
    {DataType::Bool, 1},
    {DataType::Real, 4},
};

const std::unordered_set<TACType> reusableResEax = {
    TACType::ADD,
    TACType::SUB,
    TACType::MUL,
    TACType::DIV,
    TACType::MOD,
    TACType::LESS,
    TACType::GREATER,
    TACType::LESSEQUAL,
    TACType::GREATEREQUAL,
    TACType::EQUAL,
    TACType::NOTEQUAL,
    TACType::AND,
    TACType::OR,
    TACType::NOT,
    TACType::CALL  // call leaves its return value in %eax
};

const std::unordered_set<SymbolType> memorySym = {
    SymbolType::Temp,
    SymbolType::VarId,
    SymbolType::Local,
    SymbolType::VecId
};

const std::array<std::string, 6> argumentLoc = {
    "%edi", // 1st argument
    "%esi", // 2nd argument
    "%edx", // 3rd argument
    "%ecx", // 4th argument
    "%r8d", // 5th argument
    "%r9d", // 6th argument
};

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym, int index) {
    std::string res = "";
    
    switch(sym->symType) {
        case SymbolType::Integer: {
            res = "$" + std::to_string(std::stoi(sym->content)); // If I do it directly it breaks at 0
            break;
        }

        case SymbolType::Char: {
            res = "$" + std::to_string(static_cast<int>(sym->content[1]));
            break;
        }

        case SymbolType::Float:
        case SymbolType::String: {
            res = sym->label + "(%rip)";
            break;
        }

        case SymbolType::Bool: {
            res = "$" + std::to_string(((sym->content == "true") ? 1 : 0));
            break;
        }

        case SymbolType::Temp:
        case SymbolType::Local:
        case SymbolType::VarId: {
            res = sym->content + ( sym->inStack ? "(%rbp)" : "(%rip)");
            break;
        }

        case SymbolType::VecId: {
            if(index >= 0)
                res = std::to_string(dataSizeTable[sym->dataType] * index) + "+" + sym->content + "(%rip)";
            else
                res = "(%rdx,%rax)";
            
            break;
        }

        default:
            break;
    }

    return res;
};

std::string getAsmDestination(Symbol* sym, int index) {
    switch(sym->symType) {
        case SymbolType::Temp:
        case SymbolType::VarId:
        case SymbolType::Local:
            return sym->content + ( sym->inStack ? "(%rbp)" : "(%rip)");

        case SymbolType::VecId:
            return ( (index > 0) ? (std::to_string(dataSizeTable[sym->dataType] * index) + "+") : "") + sym->content + "(%rip)";
        
        // These cases are illegal as L-values
        case SymbolType::Integer:
        case SymbolType::Char:
        case SymbolType::Float:
        case SymbolType::String:
        case SymbolType::Bool:
        default:
            // This will alert you if your TAC is malformed
            throw std::runtime_error("Invalid destination symbol: " + sym->content);
    }
}


TAC* goToTopTAC(TAC* code) {
    if(code == nullptr)
        return code;

    TAC* cur;

    for(cur = code; cur->prev != nullptr; cur = cur->prev);

    return cur;
}

void print_OriginalTAC(std::ostringstream& oss, TAC* code) {
    oss << "\n# TAC " << code->type << "\n";
}