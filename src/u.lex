%{
    #include "u.hpp"
%}

%option yylineno noyywrap

%%
#[^\n]*         {}                                      // line comment
[ \t\r\n]+      {}                                      // drop spaces

"nop"           { yylval.op = op_nop; return CMD0; }
"bye"           { yylval.op = op_bye; return CMD0; }

".dump"         { return pDUMP; }

":"             { return COLON; }
[a-zA-Z]+       { yylval.s = new std::string(yytext); return SYM; }

.               { yylval.c = yytext[0]; return CHAR; }  // any char
