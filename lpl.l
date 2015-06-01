%{
    #include "lpl.h"
%}

%%
[0-9]+ {yylval = atoi(yytext);return NUMBER;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"\n" {return EOL;}
%%

main(int argc,char **argv){
    int tok;
    while(tok=yylex()){
        printf("%d ",tok);
        if(tok==NUMBER)
            printf(" = %d\n",yylval);
        else 
            printf(" = %s",yytext);
        printf("\n");
    }
}
