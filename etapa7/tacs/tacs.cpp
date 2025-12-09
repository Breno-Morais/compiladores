#include "tacs.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

std::map<ASTNodeType, TACType> ASTtoTAC = {
    // OPS
    {ASTNodeType::OpAdd, TACType::ADD},
    {ASTNodeType::OpSub, TACType::SUB},
    {ASTNodeType::OpMul, TACType::MUL},
    {ASTNodeType::OpDiv, TACType::DIV},
    {ASTNodeType::OpMod, TACType::MOD},
    {ASTNodeType::OpLess, TACType::LESS},
    {ASTNodeType::OpGreater, TACType::GREATER},
    {ASTNodeType::OpAnd, TACType::AND},
    {ASTNodeType::OpOr, TACType::OR},
    {ASTNodeType::OpLessEqual, TACType::LESSEQUAL},
    {ASTNodeType::OpGreaterEqual, TACType::GREATEREQUAL},
    {ASTNodeType::OpEqual, TACType::EQUAL},
    {ASTNodeType::OpNotEqual, TACType::NOTEQUAL},
};

std::map<TACType, DataType> tacDefaultType = {
    {TACType::ADD, DataType::Int },
    {TACType::SUB, DataType::Int },
    {TACType::MUL, DataType::Int },
    {TACType::DIV, DataType::Int },
    {TACType::MOD, DataType::Int },
    {TACType::LESS, DataType::Bool },
    {TACType::GREATER, DataType::Bool },
    {TACType::AND, DataType::Bool },
    {TACType::OR, DataType::Bool },
    {TACType::LESSEQUAL, DataType::Bool },
    {TACType::GREATEREQUAL, DataType::Bool },
    {TACType::EQUAL, DataType::Bool },
    {TACType::NOTEQUAL, DataType::Bool },
    {TACType::NOT, DataType::Bool },
    {TACType::SYMBOL, DataType::None },	
    {TACType::VECACCESS, DataType::None },	
    {TACType::MOVE, DataType::None },	
    {TACType::MOVEVEC, DataType::None },	
    {TACType::LABEL, DataType::None },	
    {TACType::BEGINFUN, DataType::None },	
    {TACType::ENDFUN, DataType::None },	
    {TACType::IFZ, DataType::None },	
    {TACType::JUMP, DataType::None },	
    {TACType::CALL, DataType::None },	
    {TACType::ARG, DataType::None },	
    {TACType::RET, DataType::None },	
    {TACType::PRINT, DataType::None },	
    {TACType::READ, DataType::None },
};

TAC::TAC(TACType type, Symbol* res, Symbol* op1, Symbol* op2)
            : type(type), res(res), op1(op1), op2(op2), prev(nullptr), next(nullptr) {
                prev=next=nullptr;

                if(res && res->dataType == DataType::None)
                    res->dataType = tacDefaultType[type];
            }

void tacPrint(TAC* t) {
    if(!t) return;
    // if(t->type == TACType::SYMBOL) return;

    if(t->type != TACType::LABEL) std::cout << "                ";

    std::cout << t->type << " ";
    if(t->res) std::cout << t->res->content << " ";
    if(t->op1) std::cout << t->op1->content << " ";
    if(t->op2) std::cout << t->op2->content << " ";
    std::cout << std::endl;
}

// l must point to the bottom of the list, it will print from the top though
void tacPrintList(TAC* l) {
    if(l) {
        tacPrintList(l->prev);
        tacPrint(l);
    }
}

TAC* tacJoin(TAC* l1, TAC* l2) {
    
    if(!l1) return l2;
    if(!l2) return l1;
    
    TAC* t;
    for(t=l2; t->prev; t = t->prev);

    t->prev = l1;
    l1->next = t;
    
    return l2;
}

/* Retira a TAC t da lista, e retorna a próxima tac*/
TAC* tacRemove(TAC* t) {
    if(!t) return nullptr;

    if(t->next)
        t->next->prev = t->prev;

    if(t->prev)
        t->prev->next = t->next;

    return t->next;
}

TAC* generateCode(ASTNode* root) {
    TAC* result = createTAC(root);
    
    tacPrintList(result);
    for(TAC* cur = result; cur != nullptr; cur = cur->prev) {
        removeAllTacSymbols(cur);   
        removeDeadCode(cur);
    }
    std::cout << "\n\n";
    tacPrintList(result);    

    return result;
}

TAC* createTAC(ASTNode* root, Symbol* funcContext, int index) {
    if(!root) return 0;

    TAC* code[std::max(static_cast<int>(root->children.size()), 4)];
    TAC* result = nullptr;

    // Needs to be sure that the first 4 positions are null
    for(size_t i = 0; i < 4; i++) {
        code[i] = nullptr;
    }

    for(size_t i = 0; i < root->children.size(); i++) {
        code[i] = createTAC(
            root->children[i], 
            (root->type == ASTNodeType::FuncCall) ? root->symbol: funcContext, 
            (root->type == ASTNodeType::ArgList) ? index + 1: index
        );
    }

    switch(root->type) {
        case ASTNodeType::Unknown:
            std::cout << "Unknown AST Node in TAC Generation\n";
            break;

        case ASTNodeType::Lit:
        case ASTNodeType::Identifier:
            result = new TAC(TACType::SYMBOL, root->symbol);
            break;

        case ASTNodeType::DecFunc:
            result = tacJoin(tacJoin(tacJoin(tacJoin( new TAC(TACType::BEGINFUN, root->symbol), code[0]), code[1]),  code[2]), new TAC(TACType::ENDFUN, root->symbol) ); 
            // Maybe doesn't work because there is trash on the list
            break;

        case ASTNodeType::CmdAssign:
            if(code[0]) {
                if(code[0]->type == TACType::SYMBOL)
                    result = tacJoin( code[0], new TAC(TACType::MOVE, root->symbol, code[0]->res));
                else {
                    code[0]->res = root->symbol;
                    result = code[0];
            }}

            break;

        case ASTNodeType::CmdArrayElementAssign:
            result = tacJoin(tacJoin( code[0], code[1]), new TAC(TACType::MOVEVEC, root->symbol, code[0] ? code[0]->res : nullptr, code[1] ? code[1]->res : nullptr));
            break;

        case ASTNodeType::CmdRead:
            result = new TAC(TACType::READ, root->symbol);
            break;

        case ASTNodeType::CmdReturn:
            result = tacJoin( code[0], new TAC(TACType::RET, code[0] ? code[0]->res : nullptr));
            break;

        case ASTNodeType::PrintList:
            result = tacJoin(tacJoin(tacJoin(
                root->symbol ? new TAC(TACType::PRINT, root->symbol) : nullptr,
                code[0]),
                (code[0] && code[0]->type != TACType::PRINT) ? new TAC(TACType::PRINT, code[0]->res) : nullptr),
                code[1]
                );

            break;

        // OPS
        case ASTNodeType::OpAdd:
        case ASTNodeType::OpSub:
        case ASTNodeType::OpMul:
        case ASTNodeType::OpDiv:
        case ASTNodeType::OpMod:
        case ASTNodeType::OpLess:
        case ASTNodeType::OpGreater:
        case ASTNodeType::OpAnd:
        case ASTNodeType::OpOr:
        case ASTNodeType::OpLessEqual:
        case ASTNodeType::OpGreaterEqual:
        case ASTNodeType::OpEqual:
        case ASTNodeType::OpNotEqual:
            result = tacJoin(tacJoin(code[0],code[1]), new TAC(ASTtoTAC[root->type], makeTemp(), code[0] ? code[0]->res : nullptr, code[1] ? code[1]->res : nullptr));
            result = TACConstantFold(result);
            break;
    
        case ASTNodeType::OpNot:
            result = tacJoin(code[0], new TAC(TACType::NOT, makeTemp(), code[0] ? code[0]->res : nullptr));
            break;

        case ASTNodeType::ArrayElement:
            result = tacJoin(code[0], new TAC(TACType::VECACCESS, makeTemp(), code[0] ? code[0]->res : nullptr, root->symbol));
            break;

        case ASTNodeType::FuncCall:
            if(root->children.size() > 0) {
                result = tacJoin(code[0], new TAC(TACType::CALL, makeTemp(), root->symbol));
            } else {
                result = new TAC(TACType::CALL, makeTemp(), root->symbol);
            }
            break;

        case ASTNodeType::ArgList:
            result = tacJoin(tacJoin(
                    code[0],
                    new TAC(TACType::ARG, funcContext, code[0]->res, funcContext->params[index])),
                    code[1]
                );
                
            break;

        case ASTNodeType::CmdIf: {
            Symbol* label = makeLabel();
            result = tacJoin(tacJoin(tacJoin(
                code[0],                                                            // if condition
                new TAC(TACType::IFZ, label, code[0] ? code[0]->res : nullptr)),    // jump to label
                code[1]),                                                           // block
                new TAC(TACType::LABEL, label)                                      // label
            );
            break;
        }
        
        case ASTNodeType::CmdIfElse: {
            Symbol* label1 = makeLabel();
            Symbol* label2 = makeLabel();
            result = tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(
                code[0],                                                            // if condition             
                new TAC(TACType::IFZ, label1, code[0] ? code[0]->res : nullptr)),   // jump to label1
                code[1]),                                                           // block
                new TAC(TACType::JUMP, label2)),                                    // JUMP label2
                new TAC(TACType::LABEL, label1)),                                   // label1
                code[2]),                                                           // block
                new TAC(TACType::LABEL, label2)                                     // label2
            );
            break;
        }

        case ASTNodeType::CmdWhile: {
            Symbol* label1 = makeLabel();
            Symbol* label2 = makeLabel();
            result = tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(
                new TAC(TACType::LABEL, label1),                                    // label1
                code[0]),                                                           // if condition
                new TAC(TACType::IFZ, label2, code[0] ? code[0]->res : nullptr)),   // jump to label2 se 0
                code[1]),                                                           // block
                new TAC(TACType::JUMP, label1)),                                    // volta para o início
                new TAC(TACType::LABEL, label2)                                     // label saida
            );
            break;
        }

        default:
            for(size_t i = 0; i < root->children.size(); i++) {
                result = tacJoin(result, code[i]);
            }
            break;
    }

    return result;
}

/* eL: End of list*/
void removeAllTacSymbols(TAC* eL) {
    if(!eL) return;

    if(eL->type == TACType::SYMBOL) {
        tacRemove(eL);
    }

    // Talvez tenha um memory leak mas a vida é assim mesmo
}

void removeDeadCode(TAC* eL) {
    if(!eL) return;

    if(eL->type == TACType::RET) {
        for(TAC* dead = eL->next; dead != nullptr; dead = dead->next) {
            if(dead->type == TACType::ENDFUN || dead->type == TACType::LABEL)
                break;

            tacRemove(dead);
        }
    }
}

void removeRedundancy(TAC* eL) {
    if(!eL) return;

    switch(eL->type) {
        case TACType::JUMP:
            if(eL->next && eL->next->type == TACType::LABEL && eL->res == eL->next->res) {
                tacRemove(eL);
            }
        
            break;

        default:
            break;
    }

}

static int getPowerOfTwo(int n) {
    if (n <= 0) return -1;
    if ((n & (n - 1)) == 0) { // Check if power of 2
        int shift = 0;
        while ((n >> 1) > 0) {
            n >>= 1;
            shift++;
        }
        return shift;
    }
    return -1;
}

TAC* TACConstantFold(TAC* t) {
    if(!t) return nullptr;

    if (t->op1 && t->op1->symType == SymbolType::Integer && 
        t->op2 && t->op2->symType == SymbolType::Integer) {

        std::string tempName = "";
        int val1 = std::stoi(t->op1->content);
        int val2 = std::stoi(t->op2->content);

        switch (t->type) {
            case TACType::ADD:
                tempName = std::to_string(val1 + val2);
                break;

            case TACType::SUB:
                tempName = std::to_string(val1 - val2);
                break;

            case TACType::MUL:
                tempName = std::to_string(val1 * val2);
                break;

            case TACType::DIV:
                if(val2 != 0) tempName = std::to_string(static_cast<int>(val1 / val2));
                break;

            case TACType::MOD:
                if(val2 != 0) tempName = std::to_string(val1 % val2);
                break;

            default:
                break;
        }

        if(tempName != "") {
            Symbol* newLit = insertSymbolIntoTable(const_cast<char*>(tempName.c_str()), SymbolType::Integer);
            
            t->type = TACType::MOVE;
            t->op1 = newLit;
            t->op2 = nullptr; 
            return t;
        }
    }

    // CASE One Variable, One Literal
    bool op1Lit = (t->op1 && t->op1->symType == SymbolType::Integer);
    bool op2Lit = (t->op2 && t->op2->symType == SymbolType::Integer);

    if (op1Lit || op2Lit) {
        int val = op1Lit ? std::stoi(t->op1->content) : std::stoi(t->op2->content);
        Symbol* varSym = op1Lit ? t->op2 : t->op1; // The variable part

        // ADD 0, SUB 0, MUL 1, DIV 1
        
        // x + 0  OR  0 + x  -> MOVE x
        if (t->type == TACType::ADD && val == 0) {
            t->type = TACType::MOVE;
            t->op1 = varSym;
            t->op2 = nullptr;
            return t;
        }

        // x - 0 -> MOVE x
        if (t->type == TACType::SUB && val == 0 && !op1Lit) {
            t->type = TACType::MOVE;
            t->op1 = varSym;
            t->op2 = nullptr;
            return t;
        }

        // x * 1  OR  1 * x  -> MOVE x
        if (t->type == TACType::MUL && val == 1) {
            t->type = TACType::MOVE;
            t->op1 = varSym;
            t->op2 = nullptr;
            return t;
        }

        // x / 1 -> MOVE x (Note: 1 / x is NOT x)
        if (t->type == TACType::DIV && val == 1 && !op1Lit) {
            t->type = TACType::MOVE;
            t->op1 = varSym;
            t->op2 = nullptr;
            return t;
        }

        // x * 0 OR 0 * x -> MOVE 0
        if (t->type == TACType::MUL && val == 0) {
            t->type = TACType::MOVE;
            t->op1 = insertSymbolIntoTable(const_cast<char*>("0"), SymbolType::Integer);
            t->op2 = nullptr;
            return t;
        }

        int power = getPowerOfTwo(val);
        
        // Multiplication by power of 2
        // x * 8 -> x << 3
        if (t->type == TACType::MUL && power > 0) {
            t->type = TACType::LSHIFT;
            t->op1 = varSym;
            std::string shiftStr = std::to_string(power);
            t->op2 = insertSymbolIntoTable(const_cast<char*>(shiftStr.c_str()), SymbolType::Integer);
            return t;
        }

        // Division by power of 2
        // x / 8 -> x >> 3
        if (t->type == TACType::DIV && power > 0 && !op1Lit) {
            t->type = TACType::RSHIFT;
            t->op1 = varSym;
            std::string shiftStr = std::to_string(power);
            t->op2 = insertSymbolIntoTable(const_cast<char*>(shiftStr.c_str()), SymbolType::Integer);
            return t;
        }
    }

    return t;
}



static std::string getTACTypeString(const TACType& value) {
    static const std::map<const TACType, std::string> result {
        {TACType::ADD, "ADD"},
        {TACType::SUB, "SUB"},
        {TACType::MUL, "MUL"},
        {TACType::DIV, "DIV"},
        {TACType::MOD, "MOD"},
        {TACType::LESS, "LESS"},
        {TACType::GREATER, "GREATER"},
        {TACType::AND, "AND"},
        {TACType::OR, "OR"},
        {TACType::LESSEQUAL, "LESSEQUAL"},
        {TACType::GREATEREQUAL, "GREATEREQUAL"},
        {TACType::EQUAL, "EQUAL"},
        {TACType::NOTEQUAL, "NOTEQUAL"},
        {TACType::NOT, "NOT"},
        {TACType::LSHIFT, "LSHIFT"},
        {TACType::RSHIFT, "RSHIFT"},
        {TACType::SYMBOL, "SYMBOL"},	
        {TACType::VECACCESS, "VECACCESS"},	
        {TACType::MOVE, "MOVE"},	
        {TACType::MOVEVEC, "MOVEVEC"},	
        {TACType::LABEL, "LABEL"},	
        {TACType::BEGINFUN, "BEGINFUN"},	
        {TACType::ENDFUN, "ENDFUN"},	
        {TACType::IFZ, "IFZ"},	
        {TACType::JUMP, "JUMP"},	
        {TACType::CALL, "CALL"},	
        {TACType::ARG, "ARG"},	
        {TACType::RET, "RET"},	
        {TACType::PRINT, "PRINT"},	
        {TACType::READ, "READ"},
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Tac Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const TACType& value) {
    return out << getTACTypeString(value);
};
