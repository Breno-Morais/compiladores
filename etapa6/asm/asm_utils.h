#ifndef ASM_UTILS_COMP
#define ASM_UTILS_COMP

#include "../symbols/symbols.h" // Include your symbol header
#include "../tacs/tacs.h"         // Include your TAC header

#include <unordered_set>
#include <array>
#include <string>
#include <map>

// A map for data type sizes (use 'extern' to define it once in the .cpp)
extern std::map<DataType, std::string> dataSizeTable;

// A map that defines the TACs that will leave the result into the register
extern const std::unordered_set<TACType> reusableResEax;

// The index is the same as the argument in the function, while the returning string holds the register for passing the arg
extern const std::array<std::string, 6> argumentLoc;

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym);
std::string getAsmDestination(Symbol* sym);
TAC* goToTopTAC(TAC* code);

#endif /* ASM_UTILS_COMP */