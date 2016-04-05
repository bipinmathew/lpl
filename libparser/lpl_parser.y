%right IDENT ASSN.
%right BANG SUMOVER.

%nonassoc DRAW.

%left ADD SUB.
%left MULT DIV.
%nonassoc EQ LT GT LTEQ GTEQ.


%token_type {char*}

%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <string.h>

  #include "lpl_errors.h"
  #include "parser.h"
  #include "debug.h"
  #include "queue.h"
}

%syntax_error
{
  dbg("%s\n","Got Syntax Error.");
  /* TODO Need to update error handling in the case of Queues of expressions. 
  initNode(result,NULL,NULL,scalar_error_node);
  lpl_make_error_node(*result,LPL_SYNTAX_ERROR,NULL);
  */
}


/* %default_destructor {releaseNode($$);} */


%type expr  {node*}

%type start {node*}
%type statement_list {Queue*}


%extra_argument {Queue *result}


start ::= statement_list(B) .
    {
      result = B;
    }


statement_list(B) ::= expr(A). {queue_push_tail(result,A); B=result;}
statement_list(C) ::= statement_list(A) NL. {C=A;}
statement_list(C) ::= statement_list(A) NL expr(B). {result = A; queue_push_tail(result,B); C = result;}

/* System functions */

expr(A) ::= EXIT.{free(A); exit(0);}



expr(C) ::= IDENT(A) ASSN expr(B). {
  C = assignNode(identNode(A),B);
  free(A);
}

/* End System functions */

/* Assignment */

expr(A) ::= NUMBER(B). {A = intNode(B);free(B);}
expr(A) ::= FLOAT(B).  {A = doubleNode(B);free(B);}
expr(A) ::= IDENT(B).  {A = identNode(B);free(B);}
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
expr(C) ::= expr(A) SUB expr(B). {C = subNode(A,B);}
expr(C) ::= expr(A) DIV expr(B). {C = divNode(A,B);}
expr(C) ::= expr(A) MULT expr(B). {C = multNode(A,B);}


expr(C) ::= expr(A) EQ expr(B). {C = eqNode(A,B);}
expr(C) ::= expr(A) LT expr(B). {C = ltNode(A,B);}
expr(C) ::= expr(A) GT expr(B). {C = gtNode(A,B);}
expr(C) ::= expr(A) LTEQ expr(B). {C = lteqNode(A,B);}
expr(C) ::= expr(A) GTEQ expr(B). {C = gteqNode(A,B);}

