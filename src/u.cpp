#include "u.hpp"

int main(int argc, char *argv[]) {
    // \ args
    for (int i = 0; i < argc; i++)
        printf("argv[%i] = [%s]\n", i, argv[i]);

    // / args
    return yyparse();
}

#define YYERR "\n\n" << yylineno << ":" << msg << "[" << yytext << "]\n\n"
void yyerror(std::string msg) {
    std::cout << YYERR;
    std::cerr << YYERR;
    exit(-1);
}
