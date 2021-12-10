%{
    #include "u.hpp"
%}

%option yylineno noyywrap

%%
#[^\n]*     {}                                      // line comment
[ \t\r\n]+  {}                                      // drop spaces
.           { yylval.c = yytext[0]; return CHAR; }  // any char
