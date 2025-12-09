#include "asm.h"
#include "asm_data.h"
#include "asm_utils.h"
#include "asm_handlers.h"

#include "../symbols/symbols.h"

#include <iostream>

std::string generateAsm(TAC* code) {
    std::ostringstream oss;
    std::ostringstream dataOss;
    int LCcounter = 0;

    // --- 1. Data Section ---
    auto symbolTable = getSymbolTable();
    generateDataSection(dataOss, symbolTable, LCcounter);
    generateReadOnlyStrings(oss);

    // --- 2. Code Section ---
    oss << "\t.text\n";
    
    code = goToTopTAC(code);

    while(code) {
        print_OriginalTAC(oss, code);
        switch(code->type) {
            // ------------------
            // --- Arithmetic ---
            // ------------------

            case TACType::ADD: {
                handle_BinOp(oss, code, "addl");
                break;
            }
            
            case TACType::SUB: {
                handle_BinOp(oss, code, "subl");
                break;
            }

            case TACType::MUL: {
                handle_Mul(oss, code);
                break;
            }

            case TACType::DIV: {
                handle_Div(oss, code);
                break;
            }

            case TACType::MOD: {
                handle_Mod(oss, code);
                break;
            }

            // ------------------------
            // --- Logic/Comparison ---
            // ------------------------

            case TACType::LESS: {
                handle_Cmp(oss, code, "setg");
                break;
            }

            case TACType::GREATER: {
                handle_Cmp(oss, code, "setl");
                break;
            }

            case TACType::LESSEQUAL: {
                handle_Cmp(oss, code, "setge");
                break;
            }

            case TACType::GREATEREQUAL: {
                handle_Cmp(oss, code, "setle");
                break;
            }
            
            case TACType::EQUAL: {
                handle_Cmp(oss, code, "sete");
                break;
            }

            case TACType::NOTEQUAL: {
                handle_Cmp(oss, code, "setne");
                break;
            }

            case TACType::AND: {
                handle_And(oss, code, LCcounter);
                break;
            }

            case TACType::OR: {
                handle_Or(oss, code, LCcounter);
                break;
            }

            case TACType::NOT: {
                handle_Not(oss, code);
                break;
            }

            // --------------------
            // --- Control Flow ---
            // --------------------


            case TACType::LABEL: {
                handle_Label(oss, code);
                break;
            }

            case TACType::JUMP: {
                handle_Jump(oss, code);
                break;
            }

            case TACType::IFZ: {
                handle_IfZ(oss, code);
                break;
            }
    
            case TACType::BEGINFUN: {
                handle_BeginFun(oss, code);
                break;
            }

            case TACType::ENDFUN: {
                handle_EndFun(oss, code);
                break;
            }

            case TACType::RET: {              
                handle_Return(oss, code);
                break;
            }

            case TACType::CALL: {
                handle_Call(oss, code);
                break;
            }

            case TACType::ARG: {
                handle_Arg(oss, code);
                break;
            }

            // --------------------
            // --- I/O and Move ---
            // --------------------

            case TACType::MOVE: {
                handle_Move(oss, code);
                break;
            }

            case TACType::READ: {
                handle_Read(oss, code);
                break;
            }

            case TACType::PRINT: {
                handle_Print(oss, code, LCcounter);
                break;
            }	

            case TACType::MOVEVEC: {
                handle_Move(oss, code);
                break;
            }

            case TACType::VECACCESS: {
                handle_Move(oss, code);
                break;
            }

            default: 
                break;
        }

        code = code->next;
    }

    generateTemp(dataOss, symbolTable);

    // Security end of file info
    generateFileEpilogue(oss);

    return dataOss.str() + oss.str();
}