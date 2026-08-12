%{
    #include "u.hpp"
%}

%defines %union { std::string* s; Op op; }

%token COLON
%token<s> ID

%token<op> CMD0 CMD1

%%

syntax:| syntax ex

ex  : COLON ID  { label[*$2] = Cp;
                  if (debug) fprintf(stderr,"%s:%.4X\n",$2->c_str(),Cp); }
    | CMD0      { compile($1);
                  if (debug) fprintf(stderr,"%.4X: %.2X\n",Cp-1,M[Cp-1]); }
