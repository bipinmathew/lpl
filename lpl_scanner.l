%{
    #include "lpl_parser.h"
%}

%option reentrant
%option noyywrap

%%
[0-9]*\.[0-9]+ {return FLOAT;}
[0-9]+ {return NUMBER;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
[ \t]* {}
%%

