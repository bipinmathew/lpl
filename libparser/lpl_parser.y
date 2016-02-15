%right BANG SUMOVER.
%nonassoc DRAW.

%left ADD SUB.
%left MULT DIV.


%token_type {const char*}

%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <string.h>
  #include "lpl_errors.h"
  #include "node.h"
  #include "debug.h"
}

%syntax_error
{
  dbg("%s\n","Got Syntax Error.");
  result->type = scalar_error_node;
  result->value.i = LPL_SYNTAX_ERROR;
}



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

/* System functions */
expr ::= EXIT.{exit(0);}


/* End System functions */

/* Assignment */
expr(A) ::= NUMBER(B). {A = intNode(B);}
expr(A) ::= FLOAT(B).  {A = doubleNode(B);}
expr(A) ::= LPARENS expr(B) RPARENS. {A=B;}
/* End Assignment */


/* Arrays */

expr(C) ::= expr(A) DRAW expr(B). {C = drawNode(A,B);}
expr(B) ::= SUMOVER expr(A). {B = sumOverNode(A);}
expr(B) ::= BANG    expr(A). {B = bangNode(A);}

/* End Arrays */


/* All productions with an expression on the LHS need to be revisited. we are
not setting the node type correctly. We should automatically promote from the
leaf nodes. */

expr(C) ::= SUB expr(A).         {C = negNode(A);}
expr(C) ::= expr(A) ADD expr(B). {C = addNode(A,B);}
expr(C) ::= expr(A) SUB expr(B). {C = minusNode(A,B);}
expr(C) ::= expr(A) DIV expr(B). {C = divNode(A,B);}
expr(C) ::= expr(A) MULT expr(B). {C = multNode(A,B);}
expr(C) ::= expr(A) EQ expr(B). {C = eqNode(A,B);}

