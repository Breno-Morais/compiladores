// Trabalho Etapa 2 - Compiladores
// Aluno: Breno da Silva Morais - 00335794

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "tacs.h"
#include "semantic_check.h"

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
        exit(2);
    }

    // yydebug = 1;
    while(isRunning()) {
        yyparse();
    }

    if(ASTSemErrorCheck(root)) {
        std::cout << "\nExit 4\n";
        exit(4);
    }

    tacPrintList(generateCode(root));

    fclose(yyin);
    exit(0);
}