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

    std::cout << type << (symbol ? "[" + symbol->content + "]": "") << "\n";

    for (size_t i = 0; i < children.size(); i++) {
        if(children[i] == nullptr)
            continue;
            
        const bool last = (i == children.size() - 1);
        children[i]->print(prefix + (isLast ? "  " : "│ "), last);
    }
}

std::string ASTNode::generateCode(int indent) const {
    auto ind = std::string(indent * 2, ' ');

    switch (type) {
        // === LITERALS & IDENTIFIERS ===
        case ASTNodeType::Identifier:
        case ASTNodeType::Lit:
            return symbol ? symbol->content : "";

        // === TYPES ===
        case ASTNodeType::TypeChar:  return "char";
        case ASTNodeType::TypeInt:   return "int";
        case ASTNodeType::TypeFloat: return "float";
        case ASTNodeType::TypeBool:  return "bool";

        // === DECLARATIONS ===
        case ASTNodeType::DecVar:
            return ind + children[0]->generateCode() + " " + symbol->content +
                   " = " + children[1]->generateCode() + ";\n";

        case ASTNodeType::DecVarArray: {
            std::string init;
            if (children.size() > 1 && children[2]) init = " = " + children[2]->generateCode();
            return ind + children[0]->generateCode() + " " + symbol->content +
                   "[" + children[1]->generateCode() + "]" + init + ";\n";
        }

        case ASTNodeType::VetInit: {
            std::string code;
            for (auto* c : children) if (c) {
                if (!code.empty()) code += " ";
                code += c->generateCode();
            }
            return code;
        }

        case ASTNodeType::DecFunc: {
            ASTNode* returnType = children[0];
            ASTNode* param  = nullptr;
            ASTNode* localVarDecs = nullptr;
            ASTNode* block = nullptr;

            for (size_t i = 1; i < children.size(); i++) {
                switch (children[i]->type) {
                    case ASTNodeType::ParamList:        
                        param = children[i]; 
                        break;

                    case ASTNodeType::LocalVarDecList:  
                        localVarDecs = children[i]; 
                        break;

                    case ASTNodeType::Block:            
                        block = children[i]; 
                        break;

                    default: break;
                }
            }

            return ind + returnType->generateCode() + " " + symbol->content +
                   "(" + (param ? param->generateCode() : "") + ")\n" + 
                   (localVarDecs ? localVarDecs->generateCode(indent + 1) : "") +
                   (block ? block->generateCode(indent) : "");
        }

        case ASTNodeType::Param:
            return children[0]->generateCode() + " " + symbol->content;

        case ASTNodeType::ParamList: {
            std::string left = children[0] ? children[0]->generateCode() : "";
            std::string right = children[1] ? children[1]->generateCode() : "";
            if (!left.empty() && !right.empty()) return left + ", " + right;
            return left + right;
        }

        case ASTNodeType::LocalVarDecList: {
            std::string code;
            for (auto* c : children) if (c) code += c->generateCode(indent);
            return code;
        }

        // === BLOCK ===
        case ASTNodeType::Block: {
            std::string code = ind + "{\n";
            for (auto* c : children) if (c) code += c->generateCode(indent + 1);
            code += ind + "}\n";
            return code;
        }
        
        case ASTNodeType::EmptyBlock:
            return ind + "{ }\n";

        // === COMMANDS  ===
        case ASTNodeType::CmdList: {
            std::string code;
            for (auto* c : children) if (c) code += c->generateCode(indent);
            return code;
        }

        case ASTNodeType::CmdAssign:
            return ind + symbol->content + " = " + children[0]->generateCode() + ";\n";

        case ASTNodeType::CmdArrayElementAssign:
            return ind + symbol->content + "[" + children[0]->generateCode() + "] = " +
                   children[1]->generateCode() + ";\n";

        case ASTNodeType::CmdRead:
            return ind + "read " + symbol->content + ";\n";

        case ASTNodeType::CmdPrint:
            return ind + "print " + children[0]->generateCode() + ";\n";

        case ASTNodeType::CmdReturn:
            return ind + "return " + children[0]->generateCode() + ";\n";

        case ASTNodeType::CmdIf:
            return ind + "if (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent);

        case ASTNodeType::CmdIfElse:
            return ind + "if (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent) +
                   ind + "else \n" + children[2]->generateCode(indent + 1);

        case ASTNodeType::CmdWhile:
            return ind + "while (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent);

        case ASTNodeType::CmdEmpty:
            return "";
            // return ind + " ;\n";

        // === PRINT LIST ===
        case ASTNodeType::PrintList: {
            std::string code;
            if (symbol) code += symbol->content;
            for (auto* c : children) if (c) {
                if (!code.empty()) code += " ";
                code += c->generateCode();
            }
            return code;
        }

        // === FUNCTION CALL ===
        case ASTNodeType::FuncCall:
            return symbol->content + "(" +
                   (children.size() > 0 && children[0] ? children[0]->generateCode() : "") + ")";

        case ASTNodeType::ArgList: {
            std::string left = children[0] ? children[0]->generateCode() : "";
            std::string right = children[1] ? children[1]->generateCode() : "";
            if (!left.empty() && !right.empty()) return left + ", " + right;
            return left + right;
        }

        // === EXPRESSIONS ===
        case ASTNodeType::OpAdd: return children[0]->generateCode() + " + " + children[1]->generateCode();
        case ASTNodeType::OpSub: return children[0]->generateCode() + " - " + children[1]->generateCode();
        case ASTNodeType::OpMul: return children[0]->generateCode() + " * " + children[1]->generateCode();
        case ASTNodeType::OpDiv: return children[0]->generateCode() + " / " + children[1]->generateCode();
        case ASTNodeType::OpMod: return children[0]->generateCode() + " % " + children[1]->generateCode();
        case ASTNodeType::OpLess: return children[0]->generateCode() + " < " + children[1]->generateCode();
        case ASTNodeType::OpGreater: return children[0]->generateCode() + " > " + children[1]->generateCode();
        case ASTNodeType::OpEqual: return children[0]->generateCode() + " == " + children[1]->generateCode();
        case ASTNodeType::OpNotEqual: return children[0]->generateCode() + " != " + children[1]->generateCode();
        case ASTNodeType::OpLessEqual: return children[0]->generateCode() + " <= " + children[1]->generateCode();
        case ASTNodeType::OpGreaterEqual: return children[0]->generateCode() + " >= " + children[1]->generateCode();
        case ASTNodeType::OpAnd: return children[0]->generateCode() + " & " + children[1]->generateCode();
        case ASTNodeType::OpOr: return children[0]->generateCode() + " | " + children[1]->generateCode();
        case ASTNodeType::OpAssign: return children[0]->generateCode() + " = " + children[1]->generateCode();
        case ASTNodeType::OpNot: return "~" + children[0]->generateCode();

        // === TOP LEVEL ===
        case ASTNodeType::DecList: {
            std::string code;
            for (auto* c : children) if (c) code += c->generateCode(indent);
            return code;
        }
        case ASTNodeType::Program:
            return children[0]->generateCode(indent);

        default:
            return "";
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