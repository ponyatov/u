%{
    #include "u.hpp"
%}

%defines %union {
    char c;
}

%token <c> CHAR

%%
REPL :
REPL : REPL CHAR    { yyerror("unknown char"); }
