#include "node.h"
#include <stdio.h>


void Visitor::visit(Node *n){
  printf("visit generic node\n");
}


template <class T>
void Visitor::visit(TerminalNode<T>* n){
  printf("visit terminal node\n");
}


void Visitor::visit(OpNode *n){
  printf("visit op node\n");
}

Node::Node(Node *l,Node *r){
  setLeft(l);
  setRight(r);
}

Node::Node(){
  Node(NULL,NULL);
}

void Node::accept(Visitor v){
  v.visit(this);
}


Node* Node::getLeft(){
  return l;
}

Node* Node::getRight(){
  return r;
}

void Node::setLeft(Node* left){
  l = left;
}

void Node::setRight(Node* right){
  r = right;
}

OpNode::OpNode(const std::string& input, Node* left, Node* right) : Node(left,right){
  setOp(input);
}

void OpNode::setOp(const std::string& input){
  op = input;
}

void OpNode::accept(Visitor v){
  v.visit(this);
}

template <>
void TerminalNode<double>::accept(Visitor v){
  v.visit(this);
}


template <>
void TerminalNode<int>::accept(Visitor v){
  v.visit(this);
}

