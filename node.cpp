#include "node.h"
#include <stdio.h>


void Visitor::visit(Node *n){
  printf("visit generic node\n");
}

void EvalVisitor::visit(Node *n){
  printf("visit eval generic node\n");
}

void EvalVisitor::visit(OpNode* n){
  printf("visit op node\n");
}

void EvalVisitor::visit(TerminalNode<double>* n){
  printf("visit double terminal node\n");
}

void EvalVisitor::visit(TerminalNode<int>* n){
  printf("visit int terminal node\n");
}

Node::Node(Node *l,Node *r){
  setLeft(l);
  setRight(r);
}

Node::Node(){
  Node(NULL,NULL);
}

void Node::accept(Visitor* v){
  v->visit(this);
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

void OpNode::accept(Visitor* v){
  printf("Accepting OpNode...\n");
  v->visit(this);
}

template <>
void TerminalNode<double>::accept(Visitor* v){
  v->visit(this);
}


template <>
void TerminalNode<int>::accept(Visitor* v){
  v->visit(this);
}

