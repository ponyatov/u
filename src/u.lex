%{
    #include "u.hpp"
%}

%option noyywrap yylineno

%%
\#\![^\n]+      {}                  // ignore shebang
\#[^\n]+        {}                  // line comment
[ \t\r\n]+      {}                  // drop whitespaces

:               { return COLON; }

"nop"           { yylval.op = Op::nop ; return CMD0; }
"halt"          { yylval.op = Op::halt; return CMD0; }

[_a-zA-Z][_a-zA-Z0-9]* { yylval.s = new std::string(yytext); return ID; }

.               { yyerror(""); }    // on any undetected char
