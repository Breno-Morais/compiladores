#ifndef TACS_H
#define TACS_H

#include "../symbols/symbols.h"
#include "../ast/ast.h"

enum class TACType {
    // OPS
    ADD,
    SUB,
    MUL,
    DIV,
    ASSIGN,
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

        TAC(TACType type, Symbol* res = nullptr, Symbol* op1 = nullptr, Symbol* op2 = nullptr)
            : type(type), res(res), op1(op1), op2(op2), prev(nullptr), next(nullptr) {prev=next=nullptr; }
};

void tacPrint(TAC* t);
void tacPrintList(TAC* l);
TAC* tacJoin(TAC* l1, TAC* l2);

TAC* generateCode(ASTNode* root, Symbol* funcContext = nullptr, int index = 0);

std::ostream& operator<<(std::ostream& out, const TACType& value);

#endif // TACS_H