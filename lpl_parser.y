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
%type start {Node*}
%extra_argument {bool* valid}

start ::= expr(B) . 
    {
        EvalVisitor *v = new EvalVisitor();
        std::stack<Node*> S = v->S;
        Node* t;
        S.push(B);
        while(!S.empty()){
          t=S.top();
          if(t->getLeft()!=NULL){
            t->getLeft()->accept(v);
          } 
          if(t->getRight()!=NULL){
            t->getRight()->accept(v);
          }
          t->accept(v); 
          S.pop();
        }
    }

expr(C)  ::= NUMBER(A) PLUS NUMBER(B) . 
    {
        C = new OpNode("+",new intNode(atoi(A)),new intNode(atoi(B)));
    }

expr(C)  ::= FLOAT(A) PLUS FLOAT(B) . 
    {
        C = new OpNode("+",new doubleNode(atof(A)),new doubleNode(atof(B)));
    }

expr(C)  ::= FLOAT(A) PLUS NUMBER(B) . 
    {
        C = new OpNode("+",new doubleNode(atof(A)),new intNode(atof(B)));
    }


expr(C)  ::= NUMBER(A) PLUS FLOAT(B) . 
    {
        C = new OpNode("+",new intNode(atof(A)),new doubleNode(atof(B)));
    }

expr(C) ::= expr(A) PLUS NUMBER(B) .
    {
        C = new OpNode("+",A,new intNode(atoi(B)));
    }

expr(C) ::= expr(A) PLUS FLOAT(B) .
    {
        C = new OpNode("+",A,new doubleNode(atof(B)));
    }
