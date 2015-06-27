#include "node.h"
#include <stdio.h>


Node::Node(Node *l,Node *r){
  setLeft(l);
  setRight(r);
}

Node::Node(){
  Node(NULL,NULL);
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

