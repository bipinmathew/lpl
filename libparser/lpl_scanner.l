%{
    int fileno(FILE *stream);
    #include "lpl_parser.h"
%}

%option reentrant
%option noyywrap

%%

[ \t] {}

[0-9]*\.[0-9]+ {return FLOAT;}
[0-9]+ {return NUMBER;}


"+" {return ADD;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"(" {return LPARENS;}
")" {return RPARENS;}


_draw {return DRAW;}
"+/" {return SUMOVER;}

%%

