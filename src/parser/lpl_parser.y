%left ADD SUB.
%left MULT DIV.

%token_type {const char*}

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
  throw syntaxError();
}

%type expr {Node*}
%type start {Node*}
%extra_argument {Node **result}


start ::= expr(B) . 
{
  *result = B;
}


/* Assignment */
expr(A) ::= NUMBER(B). {*result = A = new intNode(atoi(B));}
expr(A) ::= FLOAT(B).  {*result = A = new doubleNode(atof(B));}
expr(A) ::= LPARENS expr(B) RPARENS. {*result=A=B;}
/* End Assignment */

/* Arrays */
/* End Arrays */



/* All productions with an expression on the LHS need to be revisited. we are
not setting the node type correctly. We should automatically promote from the
leaf nodes. */

expr(C) ::= SUB expr(A).         {*result = C = new negNode(A);}
expr(C) ::= expr(A) ADD expr(B). {*result = C = new addNode(A,B);} 
expr(C) ::= expr(A) SUB expr(B). {*result = C = new subNode(A,B);} 
expr(C) ::= expr(A) DIV expr(B). {*result = C = new divNode(A,B);} 
expr(C) ::= expr(A) MULT expr(B). {*result = C = new multNode(A,B);}
