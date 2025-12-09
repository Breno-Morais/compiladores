#ifndef ASM_DATA_COMP
#define ASM_DATA_COMP

#include "../symbols/symbols.h"
#include <sstream>
#include <map>
#include <string>

// Generates the entire data section by iterating the symbol table
void generateDataSection(std::ostringstream& oss, 
                         std::map<std::string, Symbol*>& symbolTable, 
                         int& LCCounter);

void generateTemp(std::ostringstream& oss, std::map<std::string, Symbol*>& symbolTable);

// Generates the .rodata strings (like "%d", "true", etc.)
void generateReadOnlyStrings(std::ostringstream& oss);

void generateFileEpilogue(std::ostringstream& oss);

// Helper for data generation
std::string convertToAsm(const std::string& valueString, DataType dataType);
std::string convertToAsmConst(const std::string& valueString, DataType dataType, DataType typeVar);

#endif /* ASM_DATA_COMP */