#ifndef COMP_AST
#define COMP_AST

#include "symbols.h"
#include <vector>
#include <string>

enum class ASTNodeType {
    Unknown, 
    Program,
    DecList,
    DecVar,
    DecVarArray,
    TypeChar,
    TypeInt,
    TypeFloat,
    TypeBool,
    Lit,
    Identifier,
    VetInit,
    DecFunc,
    ParamList,
    Param,
    LocalVarDecList,
    Block,
    CmdList,
    CmdAssign,
    CmdArrayElementAssign,
    CmdRead,
    CmdPrint,
    CmdReturn,
    CmdEmpty,
    PrintList,
    OpAdd,
    OpSub,
    OpMul,
    OpDiv,
    OpMod,
    OpLess,
    OpGreater,
    OpAssign,
    OpAnd,
    OpOr,
    OpLessEqual,
    OpGreaterEqual,
    OpEqual,
    OpNotEqual,
    OpNot,
    ArrayElement,
    FuncCall,
    ArgList,
    CmdIf,
    CmdIfElse,
    CmdWhile
};

class ASTNode {
    ASTNodeType type;
    std::vector<ASTNode*> children;
    Symbol* symbol; // only for leaf nodes

    public:
        ASTNode(ASTNodeType type, std::vector<ASTNode*> children = {}, Symbol* symbol = nullptr)
            : type(type), symbol(symbol) {
                this->children.reserve(children.size());
                for (auto* child : children) {
                    if (child != nullptr) {
                        this->children.push_back(child);
                    }
                }
            }

        void print(const std::string& prefix = "", bool isLast = true) const;
};

std::ostream& operator<<(std::ostream& out, const ASTNodeType& value);

#endif /* COMP_AST */