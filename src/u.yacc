%{
    #include "u.hpp"
%}

%defines %union { std::string* s; }

%token COLON
%token<s> ID

%%

syntax:| syntax ex

ex: COLON ID    { label[*$2] = Cp; fprintf(stderr,"%s:%.4X\n",$2->c_str(),Cp); }
