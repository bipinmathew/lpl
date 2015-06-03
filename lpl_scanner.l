%{
    #include "lpl_parser.h"
%}

%option reentrant
%option noyywrap

%%
[0-9]+ {yylval = atoi(yytext);return NUMBER;}
"+" {return ADD;}
%%

