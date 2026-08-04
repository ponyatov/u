#include "u.hpp"

addr Cp = 0;
addr Ip = 0;

int vm() { return 0; }

void halt() {
    if (debug) { fprintf(stderr, "halt\n\n"); }
#ifdef SDL
    GUI::fini();
#endif  // SDL
    exit(0);
}

bool debug = true;
