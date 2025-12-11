#ifndef TACS_H
#define TACS_H

#include "../symbols/symbols.h"
#include "../ast/ast.h"

#include <map>

enum class TACType {
    // OPS
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    LESS,
    GREATER,
    AND,
    OR,
    LESSEQUAL,
    GREATEREQUAL,
    EQUAL,
    NOTEQUAL,

    NOT,
    LSHIFT,
    RSHIFT,

    SYMBOL,	
    VECACCESS,	
    MOVE,	
    MOVEVEC,	
    LABEL,	
    BEGINFUN,	

    ENDFUN,	
    IFZ,	
    JUMP,	
    CALL,	
    ARG,	
    RET,	
    PRINT,	
    READ,
};

struct TAC {
    public:
        TACType type;
        Symbol* res;
        Symbol* op1;
        Symbol* op2;
        TAC* prev;
        TAC* next;

        TAC(TACType type, Symbol* res = nullptr, Symbol* op1 = nullptr, Symbol* op2 = nullptr);
};

void tacPrint(TAC* t);
void tacPrintList(TAC* l);
TAC* tacJoin(TAC* l1, TAC* l2);
TAC* tacRemove(TAC* t);

TAC* generateCode(ASTNode* root);
TAC* createTAC(ASTNode* root, Symbol* funcContext = nullptr, int index = 0);

// Otim
void removeAllTacSymbols(TAC* eL);
void removeDeadCode(TAC* eL);
void removeRedundancy(TAC* eL);
TAC* TACConstantFold(TAC* t);

std::ostream& operator<<(std::ostream& out, const TACType& value);

#endif // TACS_H