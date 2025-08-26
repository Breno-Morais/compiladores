#include "symbols.h"

#include <map>
#include <iostream>

std::map<std::string, Symbol> SymbolsTable;

int insertSymbolIntoTable(char* text, int token) {
    std::string symbol = std::string(text);

    if(SymbolsTable.find(symbol) != SymbolsTable.end())
        return token;

    SymbolType type;
    switch (token) {
        case TK_IDENTIFIER:
        case LIT_INT:
        case LIT_CHAR:
        case LIT_FLOAT:
        case LIT_STRING:
            type = static_cast<SymbolType>(token);
            break;
        
        default:
            return TOKEN_ERROR;
            break;
    }

    SymbolsTable[symbol] = Symbol{type, symbol};
    return token;
}

static std::string getTypeString(const SymbolType& value) {
    #define ADD_NAME(event) {event, #event}
    static const std::map<const SymbolType, std::string> result {
        ADD_NAME(SymbolType::Identifier),
        ADD_NAME(SymbolType::Integer),
        ADD_NAME(SymbolType::Char),
        ADD_NAME(SymbolType::Float),
        ADD_NAME(SymbolType::String),
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const SymbolType& value) {
    return out << getTypeString(value);
};

void printSymbolsTable() {
    std::cout << "Symbol Table:\n";
    for (const auto& entry : SymbolsTable) {
        std::cout << "  Token: " << entry.first
                  << ", Type: " << entry.second.type << std::endl;
    }
}