/// @file
#ifndef U_H
#define U_H

// \ include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
// / include

/// @defgroup config
/// @{
                                    /// fiber memory size, @ref byte
#define Msz 0x1000
                                    /// return stack size, @ref ucell
#define Rsz 0x100
                                    /// data stack size, @ref cell
#define Dsz 0x10

/// single byte, unsigned
typedef uint8_t   byte;
/// unsigned machine word = address, limited to 16-bit for MCU memory save
typedef uint16_t ucell;
/// signed machine word, integers +/-32767
typedef  int16_t  cell;
/// @}

/// @defgroup registers
/// @{
                                    /// current (main) fiber
extern byte M[Msz];
                                    /// compiler pointer
extern ucell Cp;
                                    /// instruction pointer
extern ucell Ip;
                                    /// data stack
extern cell D[Dsz];
                                    /// data stack pointer
extern byte Dp;
/// @}

                                    /// bytecode interpreter
extern void interpret();

/// @defgroup commands
/// @{

/// command/control mask: high bits pack call/jmp into a single cell (16K addr)
#define CMD_MASK 0b11000000
                                    /// VM command
enum op {
                                    /// `( -- )` @ref nop do nothing
    op_nop = 0x00,
                                    /// `( addr len -- )` @ref dump memory
    op_dump,
                                    /// return from nested call
    op_ret = !CMD_MASK,
                                    /// `( -- )` @ref bye stop system
    op_bye = 0xFF ^ CMD_MASK,
};

                                    /// `( -- )` do nothing
extern void nop();
                                    /// `( -- )` stop system
extern void bye();
                                    /// `( -- )` unconditional jump
extern void jmp();
                                    /// ( flag -- ) conditional jump
extern void qjmp();
                                    /// (R: -- addr ) nested call
extern void call();
                                    /// (R: addr -- ) return from nested call
extern void ret();
                                    /// `( addr len -- )` dump memory
extern void dump();

/// @}


/// @defgroup memory
/// @{
                                            /// store [u]cell to M[addr]
extern void Cstore(ucell addr, cell n);
                                            /// store byte to M[addr]
extern void Bstore(ucell addr, byte b);
/// @}

/// @defgroup compiler
/// @{
                                            /// latest LFA addr (in memory)
#define LATEST 0
                                            /// set @ref LATEST field to addr
extern void latest(ucell addr);
                                            /// compile byte
extern void Bcompile(byte b);
                                            /// compile [u]cell
extern void Ccompile(ucell n);
                                            /// compile counted string
extern void Scompile(std::string *s);
                                            /// existing labels table
extern std::map<std::string,ucell> label;
                                            /// compile label
extern void Clabel(std::string *s);
                                            /// compile Link Field Area
extern void LFA();
                                            /// compile Name Field Area
extern void NFA(std::string *s);
                                            /// compile Attribute Field Area
extern void AFA(byte a);
                                            /// compile Code Field Area as label
extern void CFA(std::string *s);
/// @}

// \ skelex
/// @defgroup parser
/// @{
                                    /// fetch token
extern int yylex();
                                    /// current line counter
extern int yylineno;
                                    /// parsed token text
extern char *yytext;
//
                                    /// parser run
extern int yyparse();
                                    /// syntax error callback
extern void yyerror(std::string msg);
#include "u.parser.hpp"
/// @}
// / skelex

#endif // U_H
