#ifndef COMP_SYM
#define COMP_SYM

#include "tokens.h"

#include <string>
#include <stdint.h>

enum class SymbolType: uint16_t {
    Identifier = TK_IDENTIFIER,
    Integer = LIT_INT,
    Char = LIT_CHAR,
    Float = LIT_FLOAT,
    String = LIT_STRING,
};

// still not sure if the map should have the content on the value, because it's always the same as the key, it feels redudant

struct Symbol {
    SymbolType type;
    std::string content;
};

int insertSymbolIntoTable(char* text, int type);
void printSymbolsTable();

std::ostream& operator<<(std::ostream& out, const SymbolType& value);

#endif /* COMP_SYM */