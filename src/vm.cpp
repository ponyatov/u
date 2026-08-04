#include "u.hpp"

byte M[Msz];
addr Cp = 0;
addr Ip = 0;

addr R[Rsz];
uint8_t Rp = 0;

cell D[Dsz];
uint8_t Dp = 0;

int vm() {
    while (true) {
        assert(Ip < Cp);
        Op op = (Op)M[Ip++];
        if (debug) fprintf(stderr, "\n%.4X: %.2X", Ip - 1, (uint8_t)op);
        switch (op) {  //
            case Op::nop:
                nop();
                break;
            case Op::halt:
                halt();
                break;
            default:
                fprintf(stderr, " ???\n\n");
                abort();
        }
    }
    return 0;
}

void nop() {
    if (debug) fprintf(stderr, "\tnop");
}

void halt() {
    if (debug) fprintf(stderr, "\thalt\n\n");
#ifdef SDL
    GUI::fini();
#endif  // SDL
    exit(0);
}

bool debug = true;
