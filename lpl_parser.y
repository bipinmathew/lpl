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

start ::= expr . 

expr(C)  ::= NUMBER(A) PLUS NUMBER(B) . 
    {
        C = new Node("+",new TerminalNode <int> (atoi(A)),new TerminalNode<int>(atoi(B)));
    }

expr(C)  ::= FLOAT(A) PLUS FLOAT(B) . 
    {
        C = new Node("+",new TerminalNode <double> (atof(A)),new TerminalNode<double>(atof(B)));
    }

expr(C)  ::= FLOAT(A) PLUS NUMBER(B) . 
    {
        C = new Node("+",new TerminalNode <double> (atof(A)),new TerminalNode<int>(atof(B)));
    }


expr(C)  ::= NUMBER(A) PLUS FLOAT(B) . 
    {
        C = new Node("+",new TerminalNode <int> (atof(A)),new TerminalNode<double>(atof(B)));
    }

expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        C = new Node("+",A,new TerminalNode<int>(atoi(B)));
    }

expr(C) ::= expr(A) PLUS FLOAT(B) .
    {
        C = new Node("+",A,new TerminalNode<double>(atof(B)));
    }
