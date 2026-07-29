#include "u.hpp"

extern int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
        yyfile = argv[i];
        assert(yyin = fopen(yyfile, "r"));
        yyparse();
        fclose(yyin);
        yyfile = nullptr;
    }
    return vm();
}
extern void arg(int argc, char *argv) {  //
    fprintf(stderr, "%i:%s\n", argc, argv);
}
