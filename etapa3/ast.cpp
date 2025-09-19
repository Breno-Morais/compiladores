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

std::string ASTNode::generateCode(int indent) const {
    auto ind = std::string(indent * 2, ' ');

    switch (type) {
        // --- literals and identifiers ---
        case ASTNodeType::Identifier:
        case ASTNodeType::Lit:
            return symbol ? symbol->content : "";

        // --- types ---
        case ASTNodeType::TypeChar: return "char";
        case ASTNodeType::TypeInt:  return "int";
        case ASTNodeType::TypeFloat:return "float";
        case ASTNodeType::TypeBool: return "bool";

        // --- variable declarations ---
        case ASTNodeType::DecVar:
            return ind + children[0]->generateCode() + " " + symbol->content +
                   " = " + children[1]->generateCode() + ";\n";

        case ASTNodeType::DecVarArray: {
            std::string init;
            if (children.size() > 1) init = " = " + children[1]->generateCode();
            return ind + children[0]->generateCode() + " " + symbol->content +
                   "[" + /* size not in symbol, could be from symbol? */ "10" + "]" + init + ";\n";
        }

        // --- vetinit recursive list ---
        case ASTNodeType::VetInit: {
            std::string code;
            for (size_t i = 0; i < children.size(); i++) {
                if (children[i]) {
                    if (!code.empty()) code += " ";
                    code += children[i]->generateCode();
                }
            }
            return code;
        }

        // --- function declaration ---
        case ASTNodeType::DecFunc: {
            std::string params;
            if (children.size() > 2) params = children[2]->generateCode();
            return ind + children[0]->generateCode() + " " + symbol->content +
                   " (" + params + ")\n" + children.back()->generateCode(indent);
        }

        // --- parameter list ---
        case ASTNodeType::Param:
            return children[0]->generateCode() + " " + symbol->content;
        case ASTNodeType::ParamList: {
            std::string code = children[0]->generateCode();
            if (children.size() > 1) code += ", " + children[1]->generateCode();
            return code;
        }

        // --- blocks and command lists ---
        case ASTNodeType::Block: {
            std::string code = ind + "{\n";
            for (auto* c : children) code += c->generateCode(indent + 1);
            code += ind + "}\n";
            return code;
        }
        case ASTNodeType::CmdList: {
            std::string code;
            for (auto* c : children) code += c->generateCode(indent);
            return code;
        }

        // --- commands ---
        case ASTNodeType::CmdAssign:
            return ind + symbol->content + " = " +
                   children[0]->generateCode() + ";\n";
        case ASTNodeType::CmdArrayElementAssign:
            return ind + children[0]->generateCode() + " = " +
                   children[1]->generateCode() + ";\n";
        case ASTNodeType::CmdPrint:
            return ind + "print " + children[0]->generateCode() + ";\n";
        case ASTNodeType::CmdRead:
            return ind + "read " + children[0]->generateCode() + ";\n";
        case ASTNodeType::CmdReturn:
            return ind + "return " + children[0]->generateCode() + ";\n";
        case ASTNodeType::CmdIf:
            return ind + "if (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent + 1);
        case ASTNodeType::CmdIfElse:
            return ind + "if (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent + 1) +
                   ind + "else " + children[2]->generateCode(indent + 1);
        case ASTNodeType::CmdWhile:
            return ind + "while (" + children[0]->generateCode() + ")\n" +
                   children[1]->generateCode(indent + 1);
        case ASTNodeType::CmdEmpty:
            return ind + ";\n";

        // --- print list (concatenation) ---
        case ASTNodeType::PrintList: {
            std::string code;
            for (auto* c : children) {
                if (!code.empty()) code += " ";
                code += c->generateCode();
            }
            if (symbol) {
                if (!code.empty()) code += " ";
                code += symbol->content;
            }
            return code;
        }

        // --- function call ---
        case ASTNodeType::FuncCall: {
            std::string args;
            if (!children.empty()) args = children[0]->generateCode();
            return symbol->content + "(" + args + ")";
        }
        case ASTNodeType::ArgList: {
            std::string code = children[0]->generateCode();
            if (children.size() > 1) code += ", " + children[1]->generateCode();
            return code;
        }

        // --- operators ---
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
        case ASTNodeType::OpNot: return "!" + children[0]->generateCode();

        // --- top-level declarations ---
        case ASTNodeType::DecList: {
            std::string code;
            for (auto* c : children) code += c->generateCode(indent);
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