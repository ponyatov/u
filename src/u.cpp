#include "u.hpp"

int main(int argc, char *argv[]) {
    // \ args
    for (int i = 0; i < argc; i++)
        printf("argv[%i] = [%s]\n", i, argv[i]);
    printf("\n");
    // / args
    // \ header
    Ccompile(LATEST);
    // / header
    yyparse();
    interpret();
    return 0;
}

void Cstore(ucell addr, cell n) { assert(addr<Msz); *(ucell*)(&M[addr]) = n; }
void Bstore(ucell addr, byte b) { assert(addr<Msz); M[addr] = b; }

void latest(ucell addr)         { Cstore(LATEST, addr); }

void Bcompile(byte  b)          { assert(Cp<Msz); Bstore(Cp++, b); }
void Ccompile(ucell n)          { assert(Cp<Msz); Cstore(Cp, n); Cp += sizeof(n); }

void Scompile(std::string *s) {
    size_t len = s->length(); assert(Cp+len<Msz); Bcompile(len);
    for (auto it=s->begin();it!=s->end();it++) Bcompile(*it);
}


void interpret() {
    for (;;) {
        assert(Ip<=Cp);
        byte op = M[Ip++];
        printf("\n%.4X: %.2X",Ip-1,op);
        switch (op & CMD_MASK) {
            case 0b01: jmp(); break;
            case 0b10: qjmp(); break;
            case 0b11: call(); break;
            case 0b00: switch (op) {
            case op_nop: nop(); break;
            case op_bye: bye(); break;
            default: yyerror("unknown command");
            }
        }
    }
}

#define YYERR "\n\n" << yylineno << ": " << msg << " [" << yytext << "]\n\n"
void yyerror(std::string msg) {
    std::cout << YYERR;
    std::cerr << YYERR;
    exit(-1);
}

byte  M[Msz];   // current (main) fiber
ucell Cp = 0;
ucell Ip = 0;

cell D[Dsz];    // data stack
byte Dp = 0;


void dump() {
    // printf("%.2X\tdump",op_dump);
    assert(Dp >= 2);
    ucell sz = D[--Dp];
    ucell addr = D[--Dp];

    // if (addr % 0x10 != 0) 
    // printf("\n");

    char ascii[0x10];
    byte asptr;
    asptr=0; memset(ascii,0,sizeof(ascii));

    for (ucell a = addr; a < addr + sz; a++) {
        if (a % 0x10 == 0) { 
            asptr=0; memset(ascii,0,sizeof(ascii));
            printf("\n%.4X:", a); }

        char c = M[a];
        if (c >= 'A' && c <= 'z') ascii[asptr++] = c; else ascii[asptr++] ='.';
        printf(" %.2X", c);

        if (a % 0x10 == 0xF) printf(ascii);
    }

    printf("\t(%s)\n",ascii);
}

void nop() {
    printf("\tnop");
}

void bye() {
    printf("\tbye\n\n");
    exit(0);
}

void jmp() {
    printf("%.4X\tjmp",Ip);
}

void qjmp() {
    printf("%.4X\t?jmp",Ip);
}

void call() {
    printf("%.4X\tcall",Ip);
}

void ret() {
    printf("\tret");
}


std::map<std::string,ucell> label;

void Clabel(std::string *s) {
    label[*s] = Ip; printf("%.4X:\t%s\n",Ip,s->c_str()); 
}

extern void LFA() {
    ucell p = Cp; latest(Cp); Ccompile(p);
}

extern void NFA(std::string *s) { Scompile(s); }

extern void AFA(byte a) { Bcompile(a); }

extern void CFA(std::string *s) {
    Clabel(s);
}
