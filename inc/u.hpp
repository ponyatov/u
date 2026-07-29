#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>

extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);

extern int yylex();
extern char *yytext;
extern char *yyfile;
extern int yylineno;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(const char *msg);
#include "u.yacc.hpp"

typedef uint8_t byte;
typedef uint32_t addr;
typedef int32_t cell;

extern addr Cp;  ///< compiler pounter
extern addr Ip;  ///< instruction pointer

extern std::map<std::string, addr> label;

/// bytecode interpreter
/// @returns int return from @ref main
extern int vm();
