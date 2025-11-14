// Trabalho Etapa 2 - Compiladores
// Aluno: Breno da Silva Morais - 00335794

#include "symbols.h"

#include <iostream>

std::map<std::string, Symbol*> SymbolsTable;

Symbol* insertSymbolIntoTable(char* text, SymbolType token) {
    std::string symbol = std::string(text);

    auto it = SymbolsTable.find(symbol);
    if(it != SymbolsTable.end())
        return it->second;

    SymbolsTable[symbol] = new Symbol{token, symbol};
    return SymbolsTable[symbol];
}

Symbol* getSymbolFromTable(std::string cont) {
    auto it = SymbolsTable.find(cont);
    if(it != SymbolsTable.end())
        return it->second;
    
    return nullptr;
}

static std::string getSTypeString(const SymbolType& value) {
    #define ADD_NAME(event) {event, #event}
    static const std::map<const SymbolType, std::string> result {
        ADD_NAME(SymbolType::Identifier),
        ADD_NAME(SymbolType::Integer),
        ADD_NAME(SymbolType::Char),
        ADD_NAME(SymbolType::Float),
        ADD_NAME(SymbolType::String),
        ADD_NAME(SymbolType::Bool),
        ADD_NAME(SymbolType::VarId),
        ADD_NAME(SymbolType::VecId),
        ADD_NAME(SymbolType::FuncId),
        ADD_NAME(SymbolType::Temp),
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Symbol Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const SymbolType& value) {
    return out << getSTypeString(value);
};

static std::string getDTypeString(const DataType& value) {
    #define ADD_NAME(event) {event, #event}
    static const std::map<const DataType, std::string> result {
        ADD_NAME(DataType::None),
        ADD_NAME(DataType::Int),
        ADD_NAME(DataType::Char),
        ADD_NAME(DataType::Bool),
        ADD_NAME(DataType::Real),
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Data Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const DataType& value) {
    return out << getDTypeString(value);
};

void printSymbolsTable() {
    std::cout << "Symbol Table:\n";
    for (const auto& entry : SymbolsTable) {
        std::cout << "  [" << entry.first
                  << ", " << entry.second->symType << "]\n";
    }
}

Symbol* makeTemp() {
    static int tempCount = 0;
    std::string tempName = "__temp" + std::to_string(tempCount++);
    return insertSymbolIntoTable(const_cast<char*>(tempName.c_str()), SymbolType::Temp);
}

Symbol* makeLabel() {
    static int tempCount = 0;
    std::string tempName = "__label" + std::to_string(tempCount++);
    return insertSymbolIntoTable(const_cast<char*>(tempName.c_str()), SymbolType::Temp);
}

std::map<std::string, Symbol*>& getSymbolTable() {
    return SymbolsTable;
}

void removeFromSymbolTable(std::string text) {
    SymbolsTable.erase(text);
}