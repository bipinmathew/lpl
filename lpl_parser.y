%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <string.h>
  #include "node.h"
}

%syntax_error
{
  result->type = terror;
}

%token_type {const char*}
%type expr {node*}
%type start {node*}
%extra_argument {node *result}

start ::= expr(B) . 
    {
      node *temp;
      memcpy(result,temp=evalNode(B),sizeof(node));
      free(temp);
      freeNode(B);
    }

/* Addition */

expr(C)  ::= NUMBER(A) PLUS NUMBER(B) . 
    {
        C = newNode("+",top,newNode(A,tint,NULL,NULL),newNode(B,tint,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS FLOAT(B) . 
    {
        C = newNode("+",top,newNode(A,tdouble,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) PLUS NUMBER(B) . 
    {
        C = newNode("+",top,newNode(A,tdouble,NULL,NULL),newNode(B,tint,NULL,NULL));
    }


expr(C)  ::= NUMBER(A) PLUS FLOAT(B) . 
    {
        C = newNode("+",top,newNode(A,tint,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        C = newNode("+",top,A,newNode(B,tint,NULL,NULL));
    }

expr(C) ::= expr(A) PLUS FLOAT(B) .
    {
        C = newNode("+",top,A,newNode(B,tdouble,NULL,NULL));
    }

/* End Addition */

/* Subtraction */


expr(C)  ::= NUMBER(A) MINUS NUMBER(B) . 
    {
        C = newNode("-",top,newNode(A,tint,NULL,NULL),newNode(B,tint,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) MINUS FLOAT(B) . 
    {
        C = newNode("-",top,newNode(A,tdouble,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) MINUS NUMBER(B) . 
    {
        C = newNode("-",top,newNode(A,tdouble,NULL,NULL),newNode(B,tint,NULL,NULL));
    }


expr(C)  ::= NUMBER(A) MINUS FLOAT(B) . 
    {
        C = newNode("-",top,newNode(A,tint,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C) ::= expr(A) MINUS NUMBER(B) .
    {
        C = newNode("-",top,A,newNode(B,tint,NULL,NULL));
    }

expr(C) ::= expr(A) MINUS FLOAT(B) .
    {
        C = newNode("-",top,A,newNode(B,tdouble,NULL,NULL));
    }

/* End Subtraction */

/* Mult */


expr(C)  ::= NUMBER(A) MULT NUMBER(B) . 
    {
        C = newNode("*",top,newNode(A,tint,NULL,NULL),newNode(B,tint,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) MULT FLOAT(B) . 
    {
        C = newNode("*",top,newNode(A,tdouble,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C)  ::= FLOAT(A) MULT NUMBER(B) . 
    {
        C = newNode("*",top,newNode(A,tdouble,NULL,NULL),newNode(B,tint,NULL,NULL));
    }


expr(C)  ::= NUMBER(A) MULT FLOAT(B) . 
    {
        C = newNode("*",top,newNode(A,tint,NULL,NULL),newNode(B,tdouble,NULL,NULL));
    }

expr(C) ::= expr(A) MULT NUMBER(B) .
    {
        C = newNode("*",top,A,newNode(B,tint,NULL,NULL));
    }

expr(C) ::= expr(A) MULT FLOAT(B) .
    {
        C = newNode("*",top,A,newNode(B,tdouble,NULL,NULL));
    }

/* End Mult */










