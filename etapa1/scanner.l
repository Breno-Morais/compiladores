%{
    #include "symbols.h"
    
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
do                                          { return KW_DO; }
while                                       { return KW_WHILE; }
read                                        { return KW_READ; }
print                                       { return KW_PRINT; }
return                                      { return KW_RETURN; }

true                                        { return LIT_TRUE; }
false                                       { return LIT_FLASE; }

"<="                                        { return OPERATOR_LE; }
">="                                        { return OPERATOR_GE; }
"=="                                        { return OPERATOR_EQ; }
"!="                                        { return OPERATOR_DIF; }

[0-9]+                                      { return insertSymbolIntoTable(yytext, LIT_INT); }
\'\\?.\'                                    { return insertSymbolIntoTable(yytext, LIT_CHAR); }
[0-9]+\.[0-9]+                              { return insertSymbolIntoTable(yytext, LIT_FLOAT); }

\"(\\.|[^\"\n\\])*\"                        { return insertSymbolIntoTable(yytext, LIT_STRING); }

[-,;:()\[\]{}=+*/%<>&|~]                    { return yytext[0]; }

[a-zA-Z\-]+[0-9\-a-zA-Z_]*                  { return insertSymbolIntoTable(yytext, TK_IDENTIFIER); }

[ \t]
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