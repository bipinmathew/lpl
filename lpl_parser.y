%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <iostream>
  #include "node.h"
}

%syntax_error
{
  *valid = false;
}

%token_type {const char*}
%type expr {Node*}
%extra_argument {bool* valid}

start ::= expr(A) . 
      {
        printf("result: %d\n",A->eval());
      }
expr(C)  ::= NUMBER(A) PLUS NUMBER(B) . 
    {
        C = new Node("+",new TerminalNode(atoi(A)),new TerminalNode(atoi(B)));
    }
expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        C = new Node("+",A,new TerminalNode(atoi(B)));
    }
