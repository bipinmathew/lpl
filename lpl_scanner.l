%{
    #include "lpl_parser.h"
%}

%option reentrant
%option noyywrap

%%
[0-9]+ {return NUMBER;}
"+" {return PLUS;}
[ \t]* {}
%%

