%{
    #include "u.hpp"
%}

%defines %union {
    char c;
    byte op;
    std::string *s;
}

%token <c> CHAR
%token <op> CMD0

%token pDUMP

%token <s> SYM
%token COLON

%%
REPL :
REPL : REPL ex

ex : CHAR       { yyerror("unknown char"); }
ex : CMD0       { Bcompile($1); }
ex : pDUMP      { D[Dp++] = 0x0000; D[Dp++] = Cp; dump(); }
ex : SYM COLON  { Clabel($1); }
ex : COLON SYM  { LFA(); NFA($2); AFA(0); CFA($2); }
