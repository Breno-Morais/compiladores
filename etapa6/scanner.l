%{
    // Trabalho Etapa 2 - Compiladores
    // Aluno: Breno da Silva Morais - 00335794

    #include "./ast/ast.h"
    #include "parser.tab.hpp"
    
    int running = 1;
    int lineNumber = 1;
%}

%x COMMENT

%%

char                                        { return KW_CHAR; }
int                                         { return KW_INT; }
float                                       { return KW_FLOAT; }
bool                                        { return KW_BOOL; }

if                                          { return KW_IF; }
else                                        { return KW_ELSE; }
while                                       { return KW_WHILE; }
read                                        { return KW_READ; }
print                                       { return KW_PRINT; }
return                                      { return KW_RETURN; }

true                                        {  yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Bool); return LIT_TRUE; }
false                                       {  yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Bool); return LIT_FLASE; }

"<="                                        { return OPERATOR_LE; }
">="                                        { return OPERATOR_GE; }
"=="                                        { return OPERATOR_EQ; }
"!="                                        { return OPERATOR_DIF; }

[0-9]+                                      { yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Integer); return LIT_INT; }
\'\\?.\'                                    { yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Char); return LIT_CHAR; }
[0-9]+\.[0-9]+                              { yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Float); return LIT_FLOAT; }

\"(\\.|[^\"\n\\])*\"                        { yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::String); return LIT_STRING; }

[-,;:()\[\]{}=+*/%<>&|~]                    { return yytext[0]; }

[a-zA-Z\-_]+[0-9\-a-zA-Z_]*                 { yylval.symbol = insertSymbolIntoTable(yytext, SymbolType::Identifier); return TK_IDENTIFIER; }

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