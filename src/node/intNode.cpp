#include "node.h"
#include <iostream>
#include "debug.h"

intNode::intNode(){dbg("intNode default constructor."<<std::endl);}
intNode::intNode(int value) : elementaryNode<int> (value){dbg("intNode int constructor."<<std::endl);}
void intNode::accept(Visitor* _v){_v->visit(this);}
void intNode::identify(){std::cout<<"I am a int node."<<std::endl;}
Node* intNode::clone(){return new intNode(*this);}


Node* intNode::operator+(   Node& r){
      return r+(*this);
}
Node* intNode::operator+(   doubleNode& r){
  dbg("int class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* intNode::operator+(   intNode& r){
  dbg("int class doing int addition"<<std::endl);
  return new intNode(getValue()+r.getValue());
}

Node* intNode::operator-(   Node& r){
      return r-(*this);
}
Node* intNode::operator-(   doubleNode& r){
  dbg("int class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
Node* intNode::operator-(   intNode& r){
  dbg("int class doing int subtraction"<<std::endl);
  return new intNode(getValue()-r.getValue());
}

Node* intNode::operator/(   Node& r){
      return r/(*this);
}
Node* intNode::operator/(   doubleNode& r){
  dbg("int class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
Node* intNode::operator/(   intNode& r){
  dbg("int class doing int division"<<std::endl);
  return new intNode(getValue()/r.getValue());
}

Node* intNode::operator*(   Node& r){
      return r*(*this);
}
Node* intNode::operator*(   doubleNode& r){
  dbg("int class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
Node* intNode::operator*(   intNode& r){
  dbg("int class doing int multiplication"<<std::endl);
  return new intNode(getValue()*r.getValue());
}

bool intNode::operator==(   Node& r){
      return r==(*this);
}
bool intNode::operator==(   doubleNode& r){
  dbg("int comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool intNode::operator==(   intNode& r){
  dbg("int comparing int node"<<std::endl);
  return getValue()==r.getValue();
}

