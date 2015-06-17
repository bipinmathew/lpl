#include "node.h"
#include <stdio.h>

int Node::eval(){
    if(op=="+"){
        return( evalLeft()+evalRight());
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


int Node::evalLeft(){
    return l->eval();
}

int Node::evalRight(){
    return r->eval();
}

TerminalNode::TerminalNode(int value){
    printf("Setting Value to: %d\n",value);
    setValue(value);
}


void TerminalNode::setValue(int value){
    v=value;
}


int TerminalNode::eval(){
    return(v);
}
