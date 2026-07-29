#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);

extern int yylex();
extern char *yytext;
extern char *yyfile;
extern int yylineno;
extern FILE *yyin;
extern void yyerror(const char *msg);
