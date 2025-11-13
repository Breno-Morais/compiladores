#include "asm.h"
#include "../symbols/symbols.h"

#include <iostream>
#include <sstream>      // For std::ostringstream
#include <stdexcept>    // For std::runtime_error
#include <cstdint>      // For uint32_t
#include <cstring>      // For std::memcpy
#include <cassert>      // For static_assert

std::map<DataType, std::string> dataSizeTable = {
    {DataType::Int, "4"},
    {DataType::Char, "1"},
    {DataType::Bool, "1"},
    {DataType::Real, "4"},
};

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
}

std::string symbolToAsm(Symbol* sym) {
    std::string res;
    
    switch(sym->symType) {
        case SymbolType::Integer: {
            res = "$" + std::to_string(std::stoi(sym->content)); // If I do it directly it breaks at 0
            break;
        }

        case SymbolType::Char: {
            res = "$" + std::to_string(static_cast<int>(sym->content[1]));
            break;
        }

        case SymbolType::Float:
        case SymbolType::String: {
            res = sym->label + "(%rip)";
            break;
        }

        case SymbolType::Bool: {
            res = "$" + std::to_string(((sym->content == "true") ? 1 : 0));
            break;
        }

        case SymbolType::Temp:
        case SymbolType::VarId: {
            res = sym->content + "(%rip)";
            break;
        }

        case SymbolType::VecId: {
            // TODO:
            break;
        }

        case SymbolType::FuncId: {
            // TODO:
            break;
        }

        default:
            break;
    }

    return res;
};

TAC* goToTopTAC(TAC* code) {
    if(code == nullptr)
        return code;

    TAC* cur;

    for(cur = code; cur->prev != nullptr; cur = cur->prev);

    return cur;
}

std::string beforeCmpAsm(TAC* code) {
    return "\tmovl\t" + symbolToAsm(code->op2) + ", %eax\n"
            "\tcmpl\t" + symbolToAsm(code->op1) + ", %eax\n";
}
             
std::string afterCmpAsm(TAC* code) {
    return "\tmovzbl\t%al, %eax\n"
           "\tmovl\t%eax, " + code->res->content + "(%rip)\n";;
}

std::string generateAsm(TAC* code) {
    std::ostringstream oss;

    // Before Symbol table
    oss << "\t.text\n\t.section\t.data\n";

    auto symbolTable = getSymbolTable();
    int LCcounter = 0;

    std::map<std::string, Symbol>::iterator it;

    // Print asm of the variables and constants
    for (it = symbolTable.begin(); it != symbolTable.end(); it++) {
        Symbol& symbol = it->second;

        switch (symbol.symType) {
            case SymbolType::String:{ 
                symbol.label = ".LC" + std::to_string(LCcounter);

                oss << symbol.label + ":\n" <<
                    "\t.string " << symbol.content << "\n";

                LCcounter++;
                break;
            }

            case SymbolType::Temp: {
                // TODO: Add types to Temp

                oss << "\t.globl\t" << symbol.content << "\n"
                "\t.align 4\n"
                "\t.type\t" << symbol.content << ", @object\n"
                "\t.size\t" << symbol.content << ", 4\n"
                << symbol.content << ":\n\t.long\t0\n\n";

                break;
            }

            case SymbolType::VarId: {
                if(!symbol.value)
                    break;

                std::string size = dataSizeTable[symbol.dataType];

                oss << "\t.globl\t" << symbol.content << "\n"
                "\t.align 4\n"
                "\t.type\t" << symbol.content << ", @object\n"
                "\t.size\t" << symbol.content << ", " << size << "\n"
                << symbol.content << ":\n"
                << convertToAsm(symbol.value->symbol->content, symbol.value->symbol->dataType);

                break;
            }

            case SymbolType::VecId: {
                if(!symbol.value)
                    break;

                oss << "\t.globl\t" << symbol.content << "\n"
                "\t.align 16\n"
                "\t.type\t" << symbol.content << ", @object\n"
                "\t.size\t" << symbol.content << ", 20\n"
                << symbol.content << ":\n";

                if(symbol.value->type != ASTNodeType::DecVarArray)
                    break;

                // TODO: Talvez não der certo porque o char teria o tamanho byte enquanto que o int tem long
                if(symbol.value->children[1])
                    for(ASTNode* node = symbol.value->children[1]; node != nullptr; node = node->children[1]) {
                        if(node->children[0] && node->children[0]->symbol)
                        oss << convertToAsm(node->children[0]->symbol->content, node->children[0]->symbol->dataType);
                    }
                else if(symbol.value->children[0])
                    oss << "\t.zero " << symbol.value->children[0]->symbol->content << "\n"; // TODO: Checa se o tamanho é só int ou não

                break;
            }

            case SymbolType::Float: {
                if(symbol.value == nullptr) {
                    symbol.label = ".LC" + std::to_string(LCcounter);

                    oss << symbol.label + ":\n" << convertToAsm(symbol.content, DataType::Real);

                    LCcounter++;
                }
                break;
            }

            default:
                break;
        }
    }

    /// Print helpful strings
    oss <<  "\n._print_s:\n"
            "\t.string\t\"%s\\n\"\n";
    oss <<  "._print_d:\n"
            "\t.string\t\"%d\\n\"\n";
    oss <<  "._print_c:\n"
            "\t.string\t\"%c\\n\"\n";
    oss <<  "._print_f:\n"
            "\t.string\t\"%f\\n\"\n\n";

    oss << ".true:\n"
        "\t.string\t\"true\"\n"
        ".false:\n"
        "\t.string\t\"false\"\n\n";

    // Go back to the top
    code = goToTopTAC(code);

    while(code) {
        switch(code->type) {
            case TACType::ADD: {
                // oss << "\n; TAC ADD\n";

                if(code->prev && code->prev->res != code->op1) {
                    if(code->op1->symType == SymbolType::Integer)    
                        oss << "\tmovl\t$" << code->op1->content << ", %eax\n"; 
                    else if(code->op1->symType == SymbolType::VarId || code->op1->symType == SymbolType::Temp)
                        oss << "\tmovl\t" << code->op1->content << "(%rip), %eax\n"; 
                }

                if(code->op2->symType == SymbolType::Integer)    
                    oss << "\tmovl\t$" << code->op2->content << ", %edx\n"; 
                else if(code->op2->symType == SymbolType::VarId || code->op2->symType == SymbolType::Temp)
                    oss << "\tmovl\t" << code->op2->content << "(%rip), %edx\n"; 

                oss << "\taddl\t%edx, %eax\n";

                if(!(code->next 
                    && (code->next->op1 == code->res 
                    || (code->next->type == TACType::RET && code->next->res == code->res))))
                    if(code->res->symType == SymbolType::VarId || code->res->symType == SymbolType::Temp)
                        oss << "\tmovl\t%eax, " << code->res->content << "(%rip)\n"; 

                break;
            }
            case TACType::SUB: {
                // oss << "\n; TAC SUB\n";

                if(code->prev && code->prev->res != code->op1) {
                    if(code->op1->symType == SymbolType::Integer)    
                        oss << "\tmovl\t$" << code->op1->content << ", %eax\n"; 
                    else if(code->op1->symType == SymbolType::VarId || code->op1->symType == SymbolType::Temp)
                        oss << "\tmovl\t" << code->op1->content << "(%rip), %eax\n"; 
                }
                
                if(code->op2->symType == SymbolType::Integer)    
                    oss << "\tmovl\t$" << code->op2->content << ", %edx\n"; 
                else if(code->op2->symType == SymbolType::VarId || code->op2->symType == SymbolType::Temp)
                    oss << "\tmovl\t" << code->op2->content << "(%rip), %edx\n"; 

                oss << "\tsubl\t%edx, %eax\n";

                if(!(code->next 
                    && (code->next->op1 == code->res 
                    || (code->next->type == TACType::RET && code->next->res == code->res))))
                    if(code->res->symType == SymbolType::VarId || code->res->symType == SymbolType::Temp)
                        oss << "\tmovl\t%eax, " << code->res->content << "(%rip)\n"; 

                break;
            }

            case TACType::MUL: {
                // oss << "\n; TAC MUL\n";

                if(code->op1->symType == SymbolType::Integer && code->op2->symType == SymbolType::Integer) {
                    oss << "\tmovl\t$" << (std::stoi(code->op1->content) * std::stoi(code->op2->content)) << ", " << code->res->content << "(%rip)\n";
                } else if(code->op1->symType != SymbolType::Integer && code->op2->symType != SymbolType::Integer) {
                    oss <<
                    "\tmovl\t" << code->op1->content << "(%rip), %edx\n"
                    "\tmovl\t" << code->op2->content << "(%rip), %eax\n"
                    "\timull\t%edx, %eax\n"
                    "\tmovl\t%eax, " << code->res->content << "(%rip)\n";

                } else {
                    // Constante
                    Symbol* con;

                    // Variavel ou Temp
                    Symbol* nCon;

                    if(code->op1->symType == SymbolType::Integer) {
                        con = code->op1;
                        nCon = code->op2;
                    } else {
                        con = code->op2;
                        nCon = code->op1;
                    }

                    oss <<
                        "\tmovl\t" << nCon->content << "(%rip), %eax\n"
                        "\timull\t" << symbolToAsm(con) << ", %eax, %eax\n"
                        "\tmovl\t%eax, " << code->res->content << "(%rip)\n";
                }

                break;
            }
    // DIV,
    // MOD,
            case TACType::LESS: {
                oss << beforeCmpAsm(code);
                oss << "\tsetg\t%al\n";
                oss << afterCmpAsm(code);

                break;
            }

            case TACType::GREATER: {
                oss << beforeCmpAsm(code);
                oss << "\tsetl\t%al\n";
                oss << afterCmpAsm(code);

                break;
            }

            case TACType::LESSEQUAL: {
                oss << beforeCmpAsm(code);
                oss << "\tsetge\t%al\n";
                oss << afterCmpAsm(code);

                break;
            }

            case TACType::GREATEREQUAL: {
                oss << beforeCmpAsm(code);
                oss << "\tsetle\t%al\n";
                oss << afterCmpAsm(code);

                break;
            }
            
    // AND,
    // OR,
    // EQUAL,
    // NOTEQUAL,

    // NOT,

    // VECACCESS,
            case TACType::MOVE: {
                oss << "\tmovl\t" << symbolToAsm(code->op1) << ", " << code->res->content << "(%rip)\n";

                break;
            }
    // MOVEVEC,	
    // LABEL,	
    // IFZ,	
    // JUMP,	
    // CALL,	
    // ARG,	
    // READ,
            case TACType::PRINT: {
                if(code->res->dataType == DataType::Bool) {
                    std::string labelPrint1 = ".L" + std::to_string(LCcounter);
                    LCcounter++;
                    std::string labelPrint2 = ".L" + std::to_string(LCcounter);
                    LCcounter++;

                    oss <<
                    "\tmovzbl\t" << symbolToAsm(code->res) << ", %eax\n"
                    "\ttestb\t%al, %al\n"
                    "\tje\t" << labelPrint1 << "\n"
                    "\tleaq\t.true(%rip), %rax\n"
                    "\tjmp\t" << labelPrint2 << "\n"
                    << labelPrint1 << ":\n"
                    "\tleaq\t.false(%rip), %rax\n"
                    << labelPrint2 << ":\n"
                    "\tmovq\t%rax, %rdi\n"
                    "\tcall\tputs@PLT\n";

                    break;
                }

                oss << "\tmovl\t" << symbolToAsm(code->res) << ", %esi\n";

                oss << "\tleaq\t._print_";
                switch(code->res->dataType) {
                    case DataType::Int:
                        oss << "d";
                        break;

                    case DataType::Char:
                        oss << "c";
                        break;


                    case DataType::Real:
                        oss << "f";
                        break;

                    case DataType::None:
                        if(code->res->symType == SymbolType::String)
                            oss << "s";

                        break;
                    
                    default:
                        oss << "d";
                        break;
                }

                oss << "(%rip), %rax\n";

                oss << "\tmovq\t%rax, %rdi\n"
                        "\tmovl\t$0, %eax\n"
                        "\tcall\tprintf@PLT\n";

                break;
            }	
    
            case TACType::BEGINFUN: {
                // oss << "\n; TAC BEGINFUN\n";

                oss << "\t.text\n"
                "\t.globl\t" << code->res->content << "\n"
                "\t.type\t" << code->res->content << ", @function\n"
                << code->res->content << ":\n"
                "\tendbr64\n"
                "\tpushq\t%rbp\n"
                "\tmovq\t%rsp, %rbp\n";

                break;
            }

            case TACType::ENDFUN: {
                // oss << "\n; TAC ENDFUN\n";

                oss << "\tpopq\t%rbp\n"
                "\tret\n"
                "\t.size\t" << code->res->content << ", .-" << code->res->content << "\n";

                break;
            }

            case TACType::RET: {
                // oss << "\n; TAC RET\n";
                
                // Precisa fazer a parte do float
                if(!(code->prev && code->prev->res == code->res))
                    oss << "\tmovl\t" << symbolToAsm(code->res) << ", %eax\n";
            }

            default: 
                break;
        }

        code = code->next;
    }

    // Security end of file info
    oss << "\t.ident\t\"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0\"\n"
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

    
    return oss.str();
}