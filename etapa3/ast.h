#ifndef COMP_AST
#define COMP_AST

#include "symbols.h"
#include <vector>

enum class ASTNodeType {
    Unknown, 
    
};

class ASTNode {
    ASTNodeType type;
    std::vector<ASTNode*> children;
    Symbol* symbol; // only for leaf nodes

    public:
        ASTNode(ASTNodeType type, std::vector<ASTNode*> children = {}, Symbol* symbol = nullptr)
            : type(type), children(children), symbol(symbol) {}
};

#endif /* COMP_AST */