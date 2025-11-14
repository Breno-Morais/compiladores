#ifndef COMP_AST
#define COMP_AST

#include "../symbols/symbols.h"
#include <vector>
#include <string>

#include <iostream>

enum class ASTNodeType {
    Unknown, 
    Program,
    DecList,
    DecVar,
    DecVarArray,

    Lit,
    Identifier,
    VetInit,
    DecFunc,
    ParamList,
    Param,
    LocalVarDecList,
    Block,
    EmptyBlock,
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
    public:
        ASTNodeType type;
        std::vector<ASTNode*> children;
        Symbol* symbol; // only for leaf nodes
        ASTNode* parent;
        DataType inferedType;

        ASTNode(ASTNodeType type, std::vector<ASTNode*> children = {}, Symbol* symbol = nullptr, DataType datatype = DataType::None)
            : type(type), symbol(symbol), parent(nullptr), inferedType(DataType::None) {                
                this->children.reserve(children.size());
                for (auto* child : children) {
                    if (child != nullptr) {
                        this->children.push_back(child);
                        child->parent = this;
                    }
                }
                
                if(symbol != nullptr && datatype != DataType::None) {
                    symbol->dataType = datatype;
                    inferedType = datatype;
                }
            }

        void print(const std::string& prefix = "", bool isLast = true) const;
        std::string generateCode(int indent = 0) const;
};

std::ostream& operator<<(std::ostream& out, const ASTNodeType& value);

#endif /* COMP_AST */