// Trabalho Etapa 2 - Compiladores
// Aluno: Breno da Silva Morais - 00335794

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "./tacs/tacs.h"
#include "./semantic_check/semantic_check.h"
#include "./asm/asm.h"

int yylex(void);
int yyparse(void);

extern FILE *yyin;
extern char *yytext;
extern int yydebug;
extern ASTNode* root;
extern int syntax_error_count;

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

    // root->print();

    if(syntax_error_count > 0) {
        fprintf(stderr, "Compilation failed with %d syntax errors.\n", syntax_error_count);
        exit(3);
    }

    if(ASTSemErrorCheck(root)) {
        std::cout << "\nExit 4\n";
        exit(4);
    }

    // printSymbolsTable();
    // std::cout << "\n\n";
    // tacPrintList(generateCode(root));

    // std::string output_filename;
    // if (argc >= 3) {
    //     output_filename = argv[2];
    // } else {
    //     output_filename = std::string(argv[1]) + ".s";
    // }

    // std::ofstream out(output_filename);
    // if (!out.is_open()) {
    //     std::cerr << "Error: Could not open output file " << output_filename << std::endl;
    //     return 1;
    // }

    // out << generateAsm(generateCode(root));
    // out.close();

    // std::cout << "\n\nASM:\n\n" << generateAsm(generateCode(root));

    fclose(yyin);
    exit(0);
}