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


":" {return ASSN;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"(" {return LPARENS;}
")" {return RPARENS;}


"!"   {return BANG;}
"+/"  {return SUMOVER;}

"=="  {return EQ;}
"<"  {return LT;}
">"  {return GT;}
"<="  {return LTEQ;}
">="  {return GTEQ;}


_draw {return DRAW;}


[_a-zA-Z][_a-zA-Z0-9]*  {return IDENT;}

[\r\n]*  {return NL;}


"\\" {return EXIT;}

%%

