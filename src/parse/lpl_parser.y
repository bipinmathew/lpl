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

/* %syntax_error
{
  result->type = terror;
} */

%type expr {Node*}
%type start {Node*}
%extra_argument {Node **result}


start ::= expr(B) . 
    {
      *result = (B->clone());
      std::cout<<"inside parser."<<std::endl;
      // result->identify();
      // evalVisitor *v = new evalVisitor();
      // Node *n;
      // std::cout<<"OY VEY"<<std::endl;

      // result->accept(v);
      // delete v;
    }


/* Assignment */
expr(A) ::= NUMBER(B). {A = new intNode(atoi(B));}
expr(A) ::= FLOAT(B).  {A = new doubleNode(atof(B));}
expr(A) ::= LPARENS expr(B) RPARENS. {A=B;}
/* End Assignment */

/* Arrays */
/* End Arrays */



/* All productions with an expression on the LHS need to be revisited. we are
not setting the node type correctly. We should automatically promote from the
leaf nodes. */

expr(C) ::= expr(A) ADD expr(B). {C = new addNode(A,B);} 
expr(C) ::= expr(A) SUB expr(B). {C = new subNode(A,B);} 
expr(C) ::= expr(A) DIV expr(B). {C = new divNode(A,B);} 
expr(C) ::= expr(A) MULT expr(B). {C = new multNode(A,B);} 
