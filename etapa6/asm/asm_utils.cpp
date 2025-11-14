#include "asm_utils.h"

std::map<DataType, std::string> dataSizeTable = {
    {DataType::Int, "4"},
    {DataType::Char, "1"},
    {DataType::Bool, "1"},
    {DataType::Real, "4"},
};

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym) {
    std::string res;
    
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
        case SymbolType::VarId: {
            res = sym->content + "(%rip)";
            break;
        }

        case SymbolType::VecId: {
            // TODO:
            break;
        }

        case SymbolType::FuncId: {
            // TODO:
            break;
        }

        default:
            break;
    }

    return res;
};

std::string getAsmDestination(Symbol* sym) {
    switch(sym->symType) {
        case SymbolType::Temp:
        case SymbolType::VarId:
            // This is the correct way to address a global variable
            return sym->content + "(%rip)";
        
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
