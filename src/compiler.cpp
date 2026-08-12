#include "u.hpp"

char *yyfile = nullptr;

extern void yyerror(const char *msg) {
    fprintf(stderr, "\n\n%s:%i %s [%s]\n\n", yyfile, yylineno, msg, yytext);
    abort();
}

std::map<std::string, addr> label;

addr compile(Op op) {  //
    return compile((byte)op);
}

addr compile(byte b) {  //
    assert(Cp + sizeof(b) < Msz);
    M[Cp] = b;
    return ++Cp;
}
