#include "node.h"
#include <stdio.h>

template <class T>
TerminalNode<T>* Node::eval(){
     if(op=="+"){
         evalLeft();
         evalRight();
     }
     else{
         printf("Crap!");
     }
     return 0;
}

Node::Node(const std::string& input, Node *l,Node *r){
    op = input;
    setLeft(l);
    setRight(r);
}

void Node::setLeft(Node* left){
    l = left;
}

void Node::setRight(Node* right){
    r = right;
}

template <class T>
TerminalNode<T>* Node::evalLeft(){
    return l->eval();
}

template <class T>
TerminalNode<T>* Node::evalRight(){
    return r->eval();
}

