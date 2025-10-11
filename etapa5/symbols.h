#ifndef COMP_SYM
#define COMP_SYM

#include <string>
#include <stdint.h>
#include <vector>

enum class SymbolType: uint16_t {
    Identifier,
    Integer,
    Char,
    Float,
    String,
    Bool,
    
    VarId,
    VecId,
    FuncId,
};

enum class DataType: uint8_t {
    None,
    Int,
    Char,
    Bool,
    Real
};

struct Symbol {
    SymbolType symType;
    std::string content;
    DataType dataType;

    //Used in functions
    std::vector<DataType> paramTypes;
};

Symbol* insertSymbolIntoTable(char* text, SymbolType type);
Symbol* getSymbolFromTable(std::string cont);
void printSymbolsTable();

std::ostream& operator<<(std::ostream& out, const SymbolType& value);
std::ostream& operator<<(std::ostream& out, const DataType& value);

#endif /* COMP_SYM */