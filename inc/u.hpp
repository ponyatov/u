/// @file
/// @brief VM for embedded script engine
/// @defgroup vm vm
/// @brief VM for embedded script engine
#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>

#ifdef SDL
#include <SDL2/SDL.h>
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

/// @defgroup type type
/// @brief MCU-friendly types
/// @ingroup vm
/// @{
typedef uint8_t byte;
typedef uint32_t addr;
typedef int32_t cell;
/// @}

/// @defgroup config config
/// @ingroup vm
/// @{
/// @ref M size, bytes (64K max)
#define Msz 0x10000
/// @}

/// @defgroup memory memory
/// @brief vat memory (actors runs as VM threads in a single Vat)
/// @ingroup vm
/// @{
extern addr Cp;  ///< compiler pounter
extern addr Ip;  ///< instruction pointer
                 /// @}

/// @defgroup compiler compiler
/// @brief bytecode compiler (AOT/REPL)
/// @{
extern std::map<std::string, addr> label;  ///< known sybolic labels
/// @}

/// bytecode interpreter
/// @returns int return from @ref main
extern int vm();
