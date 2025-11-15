#ifndef COMP_SYM
#define COMP_SYM

#include <string>
#include <stdint.h>
#include <vector>
#include <map>

class ASTNode;

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

    Temp,
    Label,
    Local,
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
    std::string label;
    
    // Used by variables, points to their initial value (LIT)
    ASTNode* value;

    //Used in functions
    std::vector<Symbol*> params;
    bool inStack = false; // If the symbol is being stored in the stack (arg or local var)

    int getParamIndex(Symbol* sym) {
        for (size_t i = 0; i < params.size(); ++i) {
            if (params[i] == sym) {
                return static_cast<int>(i);
            }
        }
        
        return -1;
    }
};

Symbol* insertSymbolIntoTable(char* text, SymbolType type);
Symbol* getSymbolFromTable(std::string cont);
std::map<std::string, Symbol*>& getSymbolTable();
void printSymbolsTable();
Symbol* makeTemp();
Symbol* makeLabel();
void removeFromSymbolTable(std::string text);

std::ostream& operator<<(std::ostream& out, const SymbolType& value);
std::ostream& operator<<(std::ostream& out, const DataType& value);

#endif /* COMP_SYM */