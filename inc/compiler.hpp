/// @file
/// @brief bytecode compiler (AOT/REPL)

#include "vm.hpp"

/// @defgroup compiler compiler
/// @brief bytecode compiler (AOT/REPL)
/// @{

extern std::map<std::string, addr> label;  ///< known sybolic labels

extern addr compile(Op op);
extern addr compile(byte b);

/// @}
