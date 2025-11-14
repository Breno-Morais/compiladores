#ifndef ASM_UTILS_COMP
#define ASM_UTILS_COMP

#include "../symbols/symbols.h" // Include your symbol header
#include "../tacs/tacs.h"         // Include your TAC header

#include <string>
#include <map>

// A map for data type sizes (use 'extern' to define it once in the .cpp)
extern std::map<DataType, std::string> dataSizeTable;

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym);
std::string getAsmDestination(Symbol* sym);
TAC* goToTopTAC(TAC* code);

#endif /* ASM_UTILS_COMP */