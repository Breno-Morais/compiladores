#ifndef ASM_UTILS_COMP
#define ASM_UTILS_COMP

#include "../symbols/symbols.h" // Include your symbol header
#include "../tacs/tacs.h"         // Include your TAC header

#include <unordered_set>
#include <array>
#include <string>
#include <map>
#include <sstream>

// A map for data type sizes (use 'extern' to define it once in the .cpp)
extern std::map<DataType, int> dataSizeTable;

// A set that defines the TACs that will leave the result into the register
extern const std::unordered_set<TACType> reusableResEax;

// A set which stores all the symbols that point to memory address
extern const std::unordered_set<SymbolType> memorySym;

// The index is the same as the argument in the function, while the returning string holds the register for passing the arg
extern const std::array<std::string, 6> argumentLoc;

extern std::map<Symbol*, bool> usedTemps;

// --- Utility Functions ---
std::string symbolToAsm(Symbol* sym, int index = 0);
std::string getAsmDestination(Symbol* sym, int index = 0);
void print_OriginalTAC(std::ostringstream& oss, TAC* code);
TAC* goToTopTAC(TAC* code);

#endif /* ASM_UTILS_COMP */