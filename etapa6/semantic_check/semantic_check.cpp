#include "semantic_check.h"

#include <iostream>
#include <string>

static bool areCompatible(const DataType& a, const DataType& b) {
    if (a == b) {
        return true;
    }

    if ((a == DataType::Int && b == DataType::Char) ||
        (a == DataType::Char && b == DataType::Int)) {
        return true;
    }

    return false;
}

// Top-Down pass to check declarations and uses of symbols
bool checkDeclarations(ASTNode* node) {
    if(node == nullptr)
        return false;

    bool hasError = false;

    switch (node->type) {
        case ASTNodeType::Unknown:
            hasError = true;

            break;

        // Na especificação não há nenhuma informação sobre escopos, logo parametros e variáveis são considerados a mesma coisa
        case ASTNodeType::DecVar:
        case ASTNodeType::Param: {
            Symbol* symbol = getSymbolFromTable(node->symbol->content);
            if(symbol == nullptr) {
                hasError = true;
                break;
            }

            if(symbol->symType == SymbolType::Identifier) { // It has not been specified yet
                symbol->symType = SymbolType::VarId;
            } else { // Has already been declared
                std::cout << "Symbol '" << symbol->content << "' already has been declared\n";
                hasError = true;
                break;
            }

            break;
        }

        case ASTNodeType::DecVarArray: {
            Symbol* symbol = getSymbolFromTable(node->symbol->content);
            if(symbol == nullptr) {
                hasError = true;
                break;
            }

            if(symbol->symType == SymbolType::Identifier) { // It has not been specified yet
                symbol->symType = SymbolType::VecId;
            } else { // Has already been declared
                std::cout << "Symbol '" << symbol->content << "' already has been declared\n";
                hasError = true;
                break;
            }

            int arraySize = stoi(node->children[0]->symbol->content);
            int count = 0;

            // Check initialization
            if(node->children.size() > 1)   {
                ASTNode* curNode = node->children[1];
                while (curNode->children.size() > 0){
                    count++;

                    if(!areCompatible(node->symbol->dataType, curNode->children[0]->symbol->dataType)) {
                        std::cout << "Not compatible initialization: " << node->symbol->content << ", element: " << curNode->children[0]->symbol->content << '\n';
                        hasError = true;
                        break;
                    }
                    
                    if(curNode->children.size() > 1) {
                        curNode = curNode->children[1];
                    } else
                        break;
                }
            }

            if(count != 0 && count != arraySize) {
                hasError = true;
                std::cout << "Array incorrectly initialized\n";
            }
            
            break;
        }

        case ASTNodeType::Lit:
        case ASTNodeType::Identifier:
        case ASTNodeType::ArrayElement: 
        case ASTNodeType::FuncCall: {
            // Inherit type from symbol before checking the declaration just for compatibility with the cmds
            if(node->symbol) {
                if(node->symbol->dataType == DataType::None) {
                    // std::cout << "Symbol '" << node->symbol->content << "' has no data type\n";
                    hasError = true;
                } else {
                    node->inferedType = node->symbol->dataType;
                }
            } 
        }

        case ASTNodeType::CmdAssign:
        case ASTNodeType::CmdArrayElementAssign: 
        case ASTNodeType::CmdRead: {
            if(node->symbol == nullptr) {
                std::cout << "Symbol not found\n";
                hasError = true;
                break;
            }

            if(node->symbol->symType == SymbolType::Identifier) {
                std::cout << "Symbol '" << node->symbol->content << "' has not been declared\n";
                hasError = true;
            }
            
            break;
        }

        case ASTNodeType::VetInit: {
            if(node->parent == nullptr || node->parent->inferedType == DataType::None) {
                std::cout << "Vector initialization with incorrect Variable\n";
                hasError = true;
                break;
            }

            node->inferedType = node->parent->inferedType;
            // Type of the vector elements will be checked on checkTypes function

            break;
        }
    
        case ASTNodeType::DecFunc: {
            Symbol* symbol = getSymbolFromTable(node->symbol->content);
            if(symbol == nullptr) {
                hasError = true;
                break;
            }

            if(symbol->symType == SymbolType::Identifier) { // It has not been specified yet
                symbol->symType = SymbolType::FuncId;
            } else { // Has already been declared
                std::cout << "Symbol '" << symbol->content << "' already has been declared\n";
                hasError = true;
                break;
            }

            if(node->children[0]->type == ASTNodeType::ParamList) {
                ASTNode* paramList = nullptr;
                for(paramList = node->children[0]; paramList != nullptr; paramList = paramList->children[1]) {
                    node->symbol->params.push_back(paramList->children[0]->symbol);
                }
            }

            break;
        }

        default:
            break;
    }

    if(hasError)
        return hasError;

    for (size_t i = 0; i < node->children.size(); i++)
    {
        hasError |= checkDeclarations(node->children[i]);
    }

    return hasError;
}

// Bottom-Up pass to check types in expressions
bool checkTypes(ASTNode* node) {
    if(node == nullptr)
        return false;

    bool hasError = false;

    for (size_t i = 0; i < node->children.size(); i++)
    {
        hasError |= checkTypes(node->children[i]);
    }

    if(hasError)
        return hasError;

    switch (node->type) {
        case ASTNodeType::DecVar: {
            if(node->children.size() > 0)
            hasError |= !areCompatible(node->symbol->dataType, node->children[0]->inferedType);

            node->symbol->value = node->children[0];
            node->children[0]->symbol->value = node; // Used to check if the value is used for the dec or somewhere else

            break;
        }

        case ASTNodeType::DecVarArray: {
            if(node->children.size() > 1)
                hasError |= !areCompatible(node->symbol->dataType, node->children[1]->inferedType);

            node->symbol->value = node;

            break;
        }

        case ASTNodeType::Identifier: {
            if(node->symbol->symType == SymbolType::Identifier) {
                std::cout << "Symbol '" << node->symbol->content << "' has not been declared\n";
                hasError = true;
                break;
            } else if(node->symbol->symType == SymbolType::FuncId) {
                std::cout << "Function symbol '" << node->symbol->content << "' used as variable\n";
                hasError = true;
                break;
            } else if(node->symbol->symType == SymbolType::VecId) {
                std::cout << "Vector symbol '" << node->symbol->content << "' used as variable\n";
                hasError = true;
                break;
            }

            break;
        }

        case ASTNodeType::VetInit: {
            if(node->children.size() > 0) {
                hasError |= !areCompatible(node->inferedType, node->children[0]->inferedType);
            } else {
                std::cout << "Empty vector initialization\n";
                hasError = true;
            }

            break;
        }

        case ASTNodeType::CmdAssign: {
            if(node->symbol == nullptr || node->symbol->symType != SymbolType::VarId) {
                std::cout << "Assignment to non-variable\n";
                hasError = true;
                break;
            }

            if(!areCompatible(node->symbol->dataType, node->children[0]->inferedType)) {
                hasError = true;
                std::cout << "Assignment of symbol '" << node->symbol->content << "' type not compatible\n";
            }

            break;
        }

        case ASTNodeType::CmdArrayElementAssign:  {
            if(node->symbol == nullptr || node->symbol->symType != SymbolType::VecId) {
                std::cout << "Assignment to non-vector\n";
                hasError = true;
                break;
            }

            if(node->children[0]->inferedType != DataType::Int) {
                hasError = true;
                std::cout << "Array index is not integer type\n";
            }

            if(!areCompatible(node->symbol->dataType, node->children[1]->inferedType)) {
                hasError = true;
                std::cout << "Assignment of symbol '" << node->symbol->content << "' type not compatible\n";
            }

            break;
        }

        case ASTNodeType::CmdReturn: {
            ASTNode* funcNode = nullptr;

            for(funcNode = node->parent; funcNode != nullptr; funcNode = funcNode->parent) {
                if(funcNode->type == ASTNodeType::DecFunc) {
                    if(!areCompatible(funcNode->symbol->dataType, node->children[0]->inferedType)) {
                        std::cout << "Return type not compatible with function type\n";
                        return true;
                    } else
                        return hasError;
                }
            }
        
            hasError = true;
            std::cout << "Return statement not inside a function\n";
            break;
        }

        // Operações Aritméticas
        case ASTNodeType::OpAdd:
        case ASTNodeType::OpSub:
        case ASTNodeType::OpMul:
        case ASTNodeType::OpDiv:
        case ASTNodeType::OpMod: {
            node->inferedType = node->children[0]->inferedType;

            if(node->inferedType == DataType::None) {
                std::cout << "Expression with undefined type\n";
                hasError = true;
                break;
            } else if(node->inferedType == DataType::Bool) {
                std::cout << "Expression with boolean type in arithmetic operation\n";
                hasError = true;
                break;
            }

            if(!areCompatible(node->inferedType, node->children[1]->inferedType)) {
                hasError = true;
                std::cout << "Arithmetic operation with incompatible types\n";
            }

            break;
        }

        // Operações Relacionais
        case ASTNodeType::OpLess:
        case ASTNodeType::OpGreater:
        case ASTNodeType::OpLessEqual:
        case ASTNodeType::OpGreaterEqual:
        case ASTNodeType::OpEqual:
        case ASTNodeType::OpNotEqual: {
            if(node->children[0]->inferedType == DataType::None) {
                std::cout << "Expression with undefined type\n";
                hasError = true;
                break;
            } else if(node->inferedType == DataType::Bool) {
                std::cout << "Expression with boolean type in relational operation\n";
                hasError = true;
                break;
            }

            if(!areCompatible(node->children[0]->inferedType, node->children[1]->inferedType)) {
                std::cout << "Relational operation with incompatible types\n";
            }
            
            node->inferedType = DataType::Bool;

            break;
        }
        
        case ASTNodeType::OpOr:
        case ASTNodeType::OpAnd: {
            if(node->children[0]->inferedType != DataType::Bool || node->children[1]->inferedType != DataType::Bool) {
                std::cout << "Expression with non-boolean type in logical operation\n";
                hasError = true;
                break;
            }
            
            node->inferedType = DataType::Bool;

            break;
        }

        case ASTNodeType::OpNot: {
            if(node->children[0]->inferedType != DataType::Bool) {
                std::cout << "Expression with non-boolean type in logical operation\n";
                hasError = true;
                break;
            }
            
            node->inferedType = DataType::Bool;

            break;
        }

        case ASTNodeType::ArrayElement: {
            if(!areCompatible(node->children[0]->inferedType, DataType::Int)) {
                std::cout << "Array index is not integer type\n";
                hasError = true;
            }

            break;
        }

        case ASTNodeType::FuncCall: {
            if(node->symbol == nullptr || node->symbol->symType != SymbolType::FuncId) {
                std::cout << "Call to non-function " << (node->symbol ? node->symbol->content : "") << "\n";
                hasError = true;
                break;
            }

            ASTNode* argList = nullptr;
            size_t paramCount = 0;

            if(node->children.size() > 0)
                for(argList = node->children[0]; argList != nullptr; argList = argList->children[1]) {
                    if(paramCount >= node->symbol->params.size()) {
                        std::cout << "Too many arguments in function call: " << node->symbol->content << '\n';
                        return true;
                    }

                    if(!areCompatible(node->symbol->params[paramCount]->dataType, argList->children[0]->inferedType)) {
                        std::cout << "Argument type not compatible in function call: " << node->symbol->content << '\n';
                        return true;
                    }

                    paramCount++;
                }

            if(paramCount < node->symbol->params.size()) {
                std::cout << "Too few arguments in function call: " << node->symbol->content << '\n';
                hasError = true;
            }

            node->inferedType = node->symbol->dataType;

            break;
        }

        case ASTNodeType::CmdIf: 
        case ASTNodeType::CmdIfElse:
        case ASTNodeType::CmdWhile: {
            if(node->children[0]->inferedType != DataType::Bool) {
                std::cout << "Condition expression is not boolean type\n";
                hasError = true;
            }

            break;
        }

        default:
            break;
    }

    return hasError;
}


bool ASTSemErrorCheck(ASTNode* node) {
    bool hasError = false;

    hasError |= checkDeclarations(node);

    if(!hasError)
        hasError |= checkTypes(node);

    return hasError;
}