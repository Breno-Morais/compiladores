%{
    // Trabalho Etapa 1 - Compiladores
    // Aluno: Breno da Silva Morais - 00335794

    #include "parser.tab.hpp"
    #include "symbols.h"
    
    int running = 1;
    int lineNumber = 1;

    #define DEBUG_SCANNER 0
%}

%x COMMENT

%%

char                                        { if (DEBUG_SCANNER) printf("KW_CHAR\n"); return KW_CHAR; }
int                                         { if (DEBUG_SCANNER) printf("KW_INT\n"); return KW_INT; }
float                                       { if (DEBUG_SCANNER) printf("KW_FLOAT\n"); return KW_FLOAT; }
bool                                        { if (DEBUG_SCANNER) printf("KW_BOOL\n"); return KW_BOOL; }

if                                          { if (DEBUG_SCANNER) printf("KW_IF\n"); return KW_IF; }
else                                        { if (DEBUG_SCANNER) printf("KW_ELSE\n"); return KW_ELSE; }
do                                          { if (DEBUG_SCANNER) printf("KW_DO\n"); return KW_DO; }
while                                       { if (DEBUG_SCANNER) printf("KW_WHILE\n"); return KW_WHILE; }
read                                        { if (DEBUG_SCANNER) printf("KW_READ\n"); return KW_READ; }
print                                       { if (DEBUG_SCANNER) printf("KW_PRINT\n"); return KW_PRINT; }
return                                      { if (DEBUG_SCANNER) printf("KW_RETURN\n"); return KW_RETURN; }

true                                        { if (DEBUG_SCANNER) printf("LIT_TRUE\n"); return LIT_TRUE; }
false                                       { if (DEBUG_SCANNER) printf("LIT_FLASE\n"); return LIT_FLASE; }

"<="                                        { if (DEBUG_SCANNER) printf("OPERATOR_LE\n"); return OPERATOR_LE; }
">="                                        { if (DEBUG_SCANNER) printf("OPERATOR_GE\n"); return OPERATOR_GE; }
"=="                                        { if (DEBUG_SCANNER) printf("OPERATOR_EQ\n"); return OPERATOR_EQ; }
"!="                                        { if (DEBUG_SCANNER) printf("OPERATOR_DIF\n"); return OPERATOR_DIF; }

[0-9]+                                      { if (DEBUG_SCANNER) printf("LIT_INT: %s\n", yytext); return insertSymbolIntoTable(yytext, LIT_INT); }
\'\\?.\'                                    { if (DEBUG_SCANNER) printf("LIT_CHAR: %s\n", yytext); return insertSymbolIntoTable(yytext, LIT_CHAR); }
[0-9]+\.[0-9]+                              { if (DEBUG_SCANNER) printf("LIT_FLOAT: %s\n", yytext); return insertSymbolIntoTable(yytext, LIT_FLOAT); }

\"(\\.|[^\"\n\\])*\"                        { if (DEBUG_SCANNER) printf("LIT_STRING: %s\n", yytext); return insertSymbolIntoTable(yytext, LIT_STRING); }

[-,;:()\[\]{}=+*/%<>&|~]                    { if (DEBUG_SCANNER) printf("SYMBOL: %c\n", yytext[0]); return yytext[0]; }

[a-zA-Z\-_]+[0-9\-a-zA-Z_]*                 { if (DEBUG_SCANNER) printf("TK_IDENTIFIER: %s\n", yytext); return insertSymbolIntoTable(yytext, TK_IDENTIFIER); }

[ \t\r]

"\n"                                        { ++lineNumber; }
"//".*
"/*"                                        { BEGIN(COMMENT); }
.                                           { return TOKEN_ERROR; }

<COMMENT>"*/"                               { BEGIN(INITIAL); }
<COMMENT>"\n"                               { ++lineNumber; }
<COMMENT>.

%%

int yywrap() {
    running = 0;
    return 1;
}

void initMe(void) {
    return;
}

int getLineNumber(void) {
    return lineNumber;
}

int isRunning(void) {
    return running;
}