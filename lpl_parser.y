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
        C = newNode("+",top,newNode(A,tint,NULL,NULL),newNode(B,tint,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS FLOAT(B) . 
    {
        printf("Adding floats...\n");
        C = newNode("+",top,newNode(A,tdouble,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS NUMBER(B) . 
    {
        printf("Adding floats and numbers...\n");
        C = newNode("+",top,newNode(A,tdouble,NULL,NULL),newNode(B,tint,NULL,NULL));
    }


expr(C)  ::= NUMBER(A) PLUS FLOAT(B) . 
    {
        printf("Adding number plus float...\n");
        C = newNode("+",top,newNode(A,tint,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        printf("Adding floats and numbers...\n");
        C = newNode("+",top,A,newNode(B,tint,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS FLOAT(B) .
    {
        C = newNode("+",top,A,newNode(B,tdouble,NULL,NULL));
    }
