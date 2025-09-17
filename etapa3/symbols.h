#ifndef COMP_SYM
#define COMP_SYM

#include <string>
#include <stdint.h>

enum class SymbolType: uint16_t {
    Identifier,
    Integer,
    Char,
    Float,
    String,
};

// still not sure if the map should have the content on the value, because it's always the same as the key, it feels redudant

struct Symbol {
    SymbolType type;
    std::string content;
};

Symbol* insertSymbolIntoTable(char* text, SymbolType type);
void printSymbolsTable();

std::ostream& operator<<(std::ostream& out, const SymbolType& value);

#endif /* COMP_SYM */