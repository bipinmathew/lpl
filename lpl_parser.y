%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include "node.h"
}

%syntax_error
{
  *valid = 0;
}

%token_type {const char*}
%type expr {node*}
%type start {node*}
%extra_argument {int* valid}

start ::= expr . 
    {
      printf("Eval here...\n");
    }

expr(C)  ::= NUMBER(A) PLUS NUMBER(B) . 
    {
        printf("Adding numbers...\n");
        C = newNode("+",TPLUS,newNode(A,TINT,NULL,NULL),newNode(B,TINT,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS FLOAT(B) . 
    {
        printf("Adding floats...\n");
        C = newNode("+",TPLUS,newNode(A,TDOUBLE,NULL,NULL),newNode(B,TDOUBLE,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS NUMBER(B) . 
    {
        printf("Adding floats and numbers...\n");
        C = newNode("+",TPLUS,newNode(A,TDOUBLE,NULL,NULL),newNode(B,TINT,NULL,NULL));
    }


expr(C)  ::= NUMBER(A) PLUS FLOAT(B) . 
    {
        C = newNode("+",TPLUS,newNode(A,TINT,NULL,NULL),newNode(B,TDOUBLE,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        printf("Adding expression plus number...\n");
        C = newNode("+",TPLUS,A,newNode(B,TINT,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS FLOAT(B) .
    {
        C = newNode("+",TPLUS,A,newNode(B,TDOUBLE,NULL,NULL));
    }
