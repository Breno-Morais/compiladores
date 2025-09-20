// Trabalho Etapa 2 - Compiladores
// Aluno: Breno da Silva Morais - 00335794

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "ast.h"

int yylex(void);
int yyparse(void);

extern FILE *yyin;
extern char *yytext;
extern int yydebug;
extern ASTNode* root;

int isRunning(void);
void initMe(void);
int getLineNumber(void);

int main(int argc, char **argv) {
    // int tok;
    if(argc < 2) {
        fprintf(stderr, "Call: ./a.out file_name\n");
        exit(1);
    }

    if((yyin = fopen(argv[1],"r")) == 0) {
        fprintf(stderr, "Didn't find the filename %s\n", argv[1]);
        exit(1);
    }

    // yydebug = 1;
    while(isRunning()) {
        // tok = yylex();
        // switch(tok) {
        //     case KW_CHAR: printf("Encontrei KW_CHAR \n"); break;
        //     case KW_INT: printf("Encontrei KW_INT \n"); break;
        //     case KW_FLOAT: printf("Encontrei KW_FLOAT \n"); break;
        //     case KW_BOOL: printf("Encontrei KW_BOOL \n"); break;

        //     case KW_IF: printf("Encontrei KW_IF \n"); break;
        //     case KW_ELSE: printf("Encontrei KW_ELSE \n"); break;
        //     case KW_DO: printf("Encontrei KW_DO \n"); break;
        //     case KW_WHILE: printf("Encontrei KW_WHILE \n"); break;
        //     case KW_READ: printf("Encontrei KW_READ \n"); break;
        //     case KW_PRINT: printf("Encontrei KW_PRINT \n"); break;
        //     case KW_RETURN: printf("Encontrei KW_RETURN \n"); break;

        //     case OPERATOR_LE: printf("Encontrei OPERATOR_LE \n"); break;
        //     case OPERATOR_GE: printf("Encontrei OPERATOR_GE \n"); break;
        //     case OPERATOR_EQ: printf("Encontrei OPERATOR_EQ \n"); break;
        //     case OPERATOR_DIF: printf("Encontrei OPERATOR_DIF \n"); break;

        //     case TK_IDENTIFIER: printf("Encontrei TK_IDENTIFIER %s \n", yytext); break;

        //     case LIT_INT: printf("Encontrei LIT_INT \n"); break;
        //     case LIT_CHAR: printf("Encontrei LIT_CHAR \n"); break;
        //     case LIT_FLOAT: printf("Encontrei LIT_FLOAT \n"); break;
        //     case LIT_TRUE: printf("Encontrei LIT_TRUE \n"); break;
        //     case LIT_FLASE: printf("Encontrei LIT_FLASE \n"); break;
        //     case LIT_STRING: printf("Encontrei LIT_STRING \n"); break;

        //     case TOKEN_ERROR: printf("Encontrei TOKEN_ERROR %d\n", tok); break;
            
        //     default: printf("Encontrei %c, token: %d\n", yytext[0], tok); break;
        // }
        yyparse();
    }

    root->print();
    if(argc >= 3) {
        std::ofstream out(argv[2]);
        out << root->generateCode();
        out.close();
    }

    printf("Parsing worked correctly! File has %d lines\n", getLineNumber());
    exit(0);
}