/// @file
/// @brief VM for embedded script engine

/// @defgroup vm vm
/// @brief VM for embedded script engine
#pragma once

/// bytecode interpreter
/// @returns int return from @ref main
extern int vm();

/// @defgroup type type
/// @brief MCU-friendly types
/// @ingroup vm
/// @{
typedef uint8_t byte;
typedef uint32_t addr;
typedef int32_t cell;
/// @}

/// @defgroup config config
/// @brief static config
/// @ingroup vm
/// @{

/// @ref M size, bytes (64K max)
#define Msz 0x10000

/// @ref R size, @ref addr esses
#define Rsz 0x100

/// @ref D size, @ref cell s
#define Dsz 0x10
/// @}

/// @defgroup memory memory
/// @brief vat memory (actors runs as VM threads in a single Vat)
/// @ingroup vm
/// @{
extern byte M[Msz];  ///< code/data memory
extern addr Cp;      ///< compiler pointer
extern addr Ip;      ///< instruction pointer

extern addr R[Rsz];  ///< return stack for @ref call / @ref ret
extern uint8_t Rp;   ///< @ref R pointer

extern cell D[Dsz];  ///< data stack
extern uint8_t Dp;   ///< @ref D pointer
/// @}

/// @defgroup debug debug
/// @brief runtime debug
/// @ingroup vm
/// @{
extern bool debug;  ///< debug flag

/// @}

/// @defgroup command command
/// @brief VM command set
/// @ingroup vm
/// @{

/// @brief VM command opcode
enum class Op : uint8_t {  //
    nop = 0x00,            ///< 00 `( -- )` @ref nop
    halt = 0xFF,           ///< FF `( -- )` @ref halt
    jmp = 0x01,            ///< 01 @ref addr `( -- )` @ref jmp
    qjmp = 0x02,           ///< 02 @ref addr `( -- )` @ref qjmp
    call = 0x03,           ///< 03 @ref addr `(R: -- addr )` @ref call
    ret = 0x04,            ///< 04 `(R: addr -- )` @ref ret
    gui = 0xE0,            ///< E0 `( -- )` start @ref GUI
};

extern void nop();   ///< `( -- )` empty command (do nothing)
extern void halt();  ///< `( -- )` stop the whole system
extern void exit();  ///< `(-- )` stop current actor (virtual thread)
/// @}
