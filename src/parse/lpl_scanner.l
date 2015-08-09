%{
    #include "lpl_parser.h"
%}

%option reentrant
%option noyywrap

%%
[0-9]*\.[0-9]+ {return FLOAT;}
[0-9]+ {return NUMBER;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"(" {return LPARENS;}
")" {return RPARENS;}
[ \t]* {}
%%

