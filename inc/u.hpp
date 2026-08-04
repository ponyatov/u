/// @file
/// @brief VM for embedded script engine
#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>

#ifdef SDL
#include "gui.hpp"
#endif  // SDL

/// @defgroup main main
/// @brief POSIX entry point
/// @{

/// POSIX entry point
extern int main(int argc, char *argv[]);
/// log single command line argument
extern void arg(int argc, char *argv);
/// @}

/// @defgroup syntax syntax
/// @ingroup compiler
/// @brief syntax parser interface
/// @{
extern int yylex();
extern char *yytext;
extern char *yyfile;
extern int yylineno;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(const char *msg);
#include "u.yacc.hpp"
/// @}

#include "vm.hpp"
#include "compiler.hpp"
