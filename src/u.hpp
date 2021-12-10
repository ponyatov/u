#ifndef U_H
#define U_H

// \ include
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
// / include

// \ skelex
extern int yylex();
extern int yylineno;
extern char *yytext;
//
extern int yyparse();
extern void yyerror(std::string msg);
#include "u.parser.hpp"
// / skelex

#endif // U_H
