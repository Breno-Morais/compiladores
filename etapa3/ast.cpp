#include "ast.h"
#include <iostream>
#include <map>

void ASTNode::print(const std::string& prefix, bool isLast) const {
    std::cout << prefix;

    if (!prefix.empty()) {
        if (isLast) {
            std::cout << "└─";
        } else {
            std::cout << "├─";
        }
    }

    std::cout << type;
    if (symbol) {
        std::cout << " [" << symbol->content << "]";
    }
    std::cout << "\n";

    for (size_t i = 0; i < children.size(); i++) {
        if(children[i] == nullptr)
            continue;
            
        const bool last = (i == children.size() - 1);
        children[i]->print(prefix + (isLast ? "  " : "│ "), last);
    }
}


static std::string getTypeString(const ASTNodeType& value) {
    #define ADD_NAME(event) {event, #event}
    static const std::map<const ASTNodeType, std::string> result {
        ADD_NAME(ASTNodeType::Unknown), 
        ADD_NAME(ASTNodeType::Program),
        ADD_NAME(ASTNodeType::DecList),
        ADD_NAME(ASTNodeType::DecVar),
        ADD_NAME(ASTNodeType::DecVarArray),
        ADD_NAME(ASTNodeType::TypeChar),
        ADD_NAME(ASTNodeType::TypeInt),
        ADD_NAME(ASTNodeType::TypeFloat),
        ADD_NAME(ASTNodeType::TypeBool),
        ADD_NAME(ASTNodeType::Lit),
        ADD_NAME(ASTNodeType::Identifier),
        ADD_NAME(ASTNodeType::VetInit),
        ADD_NAME(ASTNodeType::DecFunc),
        ADD_NAME(ASTNodeType::ParamList),
        ADD_NAME(ASTNodeType::Param),
        ADD_NAME(ASTNodeType::LocalVarDecList),
        ADD_NAME(ASTNodeType::Block),
        ADD_NAME(ASTNodeType::CmdList),
        ADD_NAME(ASTNodeType::CmdAssign),
        ADD_NAME(ASTNodeType::CmdArrayElementAssign),
        ADD_NAME(ASTNodeType::CmdRead),
        ADD_NAME(ASTNodeType::CmdPrint),
        ADD_NAME(ASTNodeType::CmdReturn),
        ADD_NAME(ASTNodeType::CmdEmpty),
        ADD_NAME(ASTNodeType::PrintList),
        ADD_NAME(ASTNodeType::OpAdd),
        ADD_NAME(ASTNodeType::OpSub),
        ADD_NAME(ASTNodeType::OpMul),
        ADD_NAME(ASTNodeType::OpDiv),
        ADD_NAME(ASTNodeType::OpMod),
        ADD_NAME(ASTNodeType::OpLess),
        ADD_NAME(ASTNodeType::OpGreater),
        ADD_NAME(ASTNodeType::OpAssign),
        ADD_NAME(ASTNodeType::OpAnd),
        ADD_NAME(ASTNodeType::OpOr),
        ADD_NAME(ASTNodeType::OpLessEqual),
        ADD_NAME(ASTNodeType::OpGreaterEqual),
        ADD_NAME(ASTNodeType::OpEqual),
        ADD_NAME(ASTNodeType::OpNotEqual),
        ADD_NAME(ASTNodeType::OpNot),
        ADD_NAME(ASTNodeType::ArrayElement),
        ADD_NAME(ASTNodeType::FuncCall),
        ADD_NAME(ASTNodeType::ArgList),
        ADD_NAME(ASTNodeType::CmdIf),
        ADD_NAME(ASTNodeType::CmdIfElse),
        ADD_NAME(ASTNodeType::CmdWhile)
    };
    #undef ADD_NAME
    auto it = result.find(value);
    if (it == result.end()) return "Unknown Type";
    return it->second;
};

std::ostream& operator<<(std::ostream& out, const ASTNodeType& value) {
    return out << getTypeString(value);
};