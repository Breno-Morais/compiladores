#ifndef ASM_UTILS_COMP
#define ASM_UTILS_COMP

#include "../symbols/symbols.h" // Include your symbol header
#include "../tacs/tacs.h"         // Include your TAC header

#include <unordered_set>
#include <string>
#include <map>

// A map for data type sizes (use 'extern' to define it once in the .cpp)
extern std::map<DataType, std::string> dataSizeTable;

// A map that defines the TACs that will leave the result into the register
extern const std::unordered_set<TACType> reusableResEax;

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym);
std::string getAsmDestination(Symbol* sym);
TAC* goToTopTAC(TAC* code);

#endif /* ASM_UTILS_COMP */