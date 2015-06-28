#include "node.h"
#include <stdio.h>


void Visitor::visit(Node *n){
  printf("visit generic node\n");
}

void EvalVisitor::visit(Node *n){
  printf("visit eval generic node\n");
}

void EvalVisitor::visit(OpNode* n){
  Node *v1, *v2;
  if(n->getOp() == "+"){
    v1=S.top();
    S.pop();
    v2=S.top();
    S.pop();
    (*v1)+(*v2);
    printf("Got a plus\n");
  }
  printf("visit op node\n");
}

void EvalVisitor::visit(doubleNode* n){
  S.push(n);
  printf("visit double terminal node\n");
}

void EvalVisitor::visit(intNode* n){
  S.push(n);
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
  v->visit(this);
}

void doubleNode::accept(Visitor* v){
  v->visit(this);
}

void intNode::accept(Visitor* v){
  v->visit(this);
}
//template <>
//void doubleNode::accept(Visitor* v){
//  v->visit(this);
//}


//template <>
//void intNode::accept(Visitor* v){
//  v->visit(this);
//}

