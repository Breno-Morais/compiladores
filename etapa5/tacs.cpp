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
    {ASTNodeType::OpAssign, TACType::ASSIGN},
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

void tacPrint(TAC* t) {
    if(!t) return;
    if(t->type == TACType::SYMBOL) return;

    if(t->type != TACType::LABEL) std::cout << "    ";

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

TAC* generateCode(ASTNode* root) {
    if(!root) return 0;

    TAC* code[std::max(static_cast<int>(root->children.size()), 4)];
    TAC* result = nullptr;

    // Needs to be sure that the first 4 positions are null
    for(size_t i = 0; i < 4; i++) {
        code[i] = nullptr;
    }

    for(size_t i = 0; i < root->children.size(); i++) {
        code[i] = generateCode(root->children[i]);
    }

    switch(root->type) {
        case ASTNodeType::Unknown:
            std::cout << "Unknown AST Node in TAC Generation\n";
            break;

        case ASTNodeType::DecVar:
            result = new TAC(TACType::DECVAR, root->symbol, code[0] ? code[0]->res : nullptr);
            break;

        case ASTNodeType::DecVarArray:
            result = tacJoin( code[1] , new TAC(TACType::DECVARARRAY, root->symbol, code[1] ? code[1]->res : nullptr));
            break;

        case ASTNodeType::Lit:
        case ASTNodeType::Identifier:
            result = new TAC(TACType::SYMBOL, root->symbol);
            break;

        case ASTNodeType::VetInit:
            result = tacJoin( code[1], new TAC(TACType::DECARRAYINIT,  code[0] ? code[0]->res : nullptr));
            break;

        case ASTNodeType::DecFunc:
            result = tacJoin(tacJoin(tacJoin(tacJoin( new TAC(TACType::BEGINFUN, root->symbol), code[0]), code[1]),  code[2]), new TAC(TACType::ENDFUN, root->symbol) ); 
            // Maybe doesn't work because there is trash on the list
            break;

        case ASTNodeType::Param:
            result = new TAC(TACType::DECVAR, root->symbol);
            break;

        case ASTNodeType::CmdAssign:
            result =  tacJoin( code[0], new TAC(TACType::MOVE, root->symbol, code[0] ? code[0]->res : nullptr));
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
                            code[1], 
                            code[0]),
                            root->symbol ? new TAC(TACType::PRINT, root->symbol) : nullptr),
                            code[0] ? new TAC(TACType::PRINT, code[0]->res) : nullptr
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
            break;
    
        case ASTNodeType::OpNot:
            result = tacJoin(code[0], new TAC(TACType::NOT, makeTemp(), code[0] ? code[0]->res : nullptr));
            break;

        case ASTNodeType::ArrayElement:
            result = tacJoin(code[0], new TAC(TACType::VECACCESS, makeTemp(), root->symbol, code[0] ? code[0]->res : nullptr));
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
                    new TAC(TACType::ARG, code[0]->res)),
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


static std::string getTACTypeString(const TACType& value) {
    static const std::map<const TACType, std::string> result {
        {TACType::ADD, "ADD"},
        {TACType::SUB, "SUB"},
        {TACType::MUL, "MUL"},
        {TACType::DIV, "DIV"},
        {TACType::ASSIGN, "ASSIGN"},
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
        {TACType::DECVAR, "DECVAR"},
        {TACType::DECVARARRAY, "DECVARARRAY"},
        {TACType::DECARRAYINIT, "DECARRAYINIT"},
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Tac Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const TACType& value) {
    return out << getTACTypeString(value);
};