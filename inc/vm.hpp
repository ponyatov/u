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

/// @defgroup debug debug
/// @brief runtime debug
/// @{
extern bool debug;  ///< debug flag

/// @}
