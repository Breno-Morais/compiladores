#include "asm_data.h"
#include "asm_utils.h"

#include <cstring>      // For std::memcpy
#include <cstdint>      // For uint32_t
#include <sstream>      // For std::ostringstream
#include <stdexcept>    // For std::runtime_error
#include <cassert>      // For static_assert

// Generates the entire data section by iterating the symbol table
void generateDataSection(std::ostringstream& oss, std::map<std::string, Symbol*>& symbolTable, int& LCCounter) {
    std::map<std::string, Symbol*>::iterator it;

    // Print asm of the variables and constants
    for (it = symbolTable.begin(); it != symbolTable.end(); it++) {
        Symbol* symbol = it->second;

        switch (symbol->symType) {
            case SymbolType::String:{ 
                symbol->label = ".LC" + std::to_string(LCCounter);

                oss << symbol->label + ":\n" <<
                    "\t.string " << symbol->content << "\n";

                LCCounter++;
                break;
            }

            case SymbolType::Temp: {
                // TODO: Add types to Temp

                oss << "\t.globl\t" << symbol->content << "\n"
                "\t.align 4\n"
                "\t.type\t" << symbol->content << ", @object\n"
                "\t.size\t" << symbol->content << ", 4\n"
                << symbol->content << ":\n\t.long\t0\n\n";

                break;
            }

            case SymbolType::VarId: {
                if(!symbol->value)
                    break;

                std::string size = dataSizeTable[symbol->dataType];

                oss << "\t.globl\t" << symbol->content << "\n"
                "\t.align 4\n"
                "\t.type\t" << symbol->content << ", @object\n"
                "\t.size\t" << symbol->content << ", " << size << "\n"
                << symbol->content << ":\n"
                << convertToAsm(symbol->value->symbol->content, symbol->value->symbol->dataType);

                break;
            }

            case SymbolType::VecId: {
                if(!symbol->value)
                    break;

                oss << "\t.globl\t" << symbol->content << "\n"
                "\t.align 16\n"
                "\t.type\t" << symbol->content << ", @object\n"
                "\t.size\t" << symbol->content << ", 20\n"
                << symbol->content << ":\n";

                if(symbol->value->type != ASTNodeType::DecVarArray)
                    break;

                // TODO: Talvez não der certo porque o char teria o tamanho byte enquanto que o int tem long
                if(symbol->value->children[1])
                    for(ASTNode* node = symbol->value->children[1]; node != nullptr; node = node->children[1]) {
                        if(node->children[0] && node->children[0]->symbol)
                        oss << convertToAsm(node->children[0]->symbol->content, node->children[0]->symbol->dataType);
                    }
                else if(symbol->value->children[0])
                    oss << "\t.zero " << symbol->value->children[0]->symbol->content << "\n"; // TODO: Checa se o tamanho é só int ou não

                break;
            }

            case SymbolType::Float: {
                if(symbol->value == nullptr) {
                    symbol->label = ".LC" + std::to_string(LCCounter);

                    oss << symbol->label + ":\n" << convertToAsm(symbol->content, DataType::Real);

                    LCCounter++;
                }
                break;
            }

            default:
                break;
        }
    }
}

// Generates the .rodata strings (like "%d", "true", etc.)
void generateReadOnlyStrings(std::ostringstream& oss) {
    oss <<  "\t.section\t.rodata\n"
            "\n._print_s:\n"
            "\t.string\t\"%s\"\n"
            "._print_d:\n"
            "\t.string\t\"%d\"\n"
            "._print_c:\n"
            "\t.string\t\"%c\"\n"
            "._print_f:\n"
            "\t.string\t\"%f\"\n\n"
            ".true:\n"
            "\t.string\t\"true\"\n"
            ".false:\n"
            "\t.string\t\"false\"\n\n";
}

// Helper for data generation
std::string convertToAsm(const std::string& valueString, DataType dataType) {
    std::ostringstream oss;

    switch (dataType) {
        case DataType::Char: {
            // Get the ASCII value of the first character
            int asciiValue = static_cast<int>(valueString[1]);
            oss << "\t.byte\t" << asciiValue;
            break;
        }

        case DataType::Bool: {
            // Convert "true" to 1, otherwise 0
            int boolValue = (valueString == "true") ? 1 : 0;
            oss << "\t.byte\t" << boolValue;
            break;
        }

        case DataType::Int: {
            // Parse the string as an integer
            // stoi will handle parsing "50" to 50
            oss << "\t.long\t" << std::stoi(valueString);
            break;
        }

        case DataType::Real: {
            // Parse to float, then get its 32-bit integer bit-pattern
            float floatValue = std::stof(valueString);
            uint32_t intRepresentation;

            // Ensure float is 32-bit on this platform
            static_assert(sizeof(float) == sizeof(uint32_t), "Float must be 32-bit");
            
            // Use memcpy to safely copy the bits
            std::memcpy(&intRepresentation, &floatValue, sizeof(floatValue));

            oss << "\t.long\t" << intRepresentation;
            break;
        }

        case DataType::None:
        default:
            // Handle error or uninitialized data (e.g., .zero directive)
            // For now, returning an error string or throwing is best.
            throw std::runtime_error("Cannot convert 'None' or unknown type to assembly value.");
    }

    return oss.str() + '\n';
};

void generateFileEpilogue(std::ostringstream& oss) {
    oss <<  "\t.ident\t\"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0\"\n"
            "\t.section\t.note.GNU-stack,\"\",@progbits\n"
            "\t.section\t.note.gnu.property,\"a\"\n"
            "\t.align 8\n"
            "\t.long\t1f - 0f\n"
            "\t.long\t4f - 1f\n"
            "\t.long\t5\n"
            "0:\n"
            "\t.string\t\"GNU\"\n"
            "1:\n"
            "\t.align 8\n"
            "\t.long\t0xc0000002\n"
            "\t.long\t3f - 2f\n"
            "2:\n"
            "\t.long\t0x3\n"
            "3:\n"
            "\t.align 8\n"
            "4:\n";
}
