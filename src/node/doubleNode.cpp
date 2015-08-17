#include "node.h"
#include <iostream>
#include "debug.h"

doubleNode::doubleNode(){dbg("doubleNode default constructor."<<std::endl);}
doubleNode::doubleNode(double value) : elementaryNode<double> (value){dbg("doubleNode double constructor."<<std::endl);}
void doubleNode::accept(Visitor* _v){_v->visit(this);}
void doubleNode::identify(){std::cout<<"I am a double node."<<std::endl;}
Node* doubleNode::clone(){return new doubleNode(*this);}

Node* doubleNode::operator+(  Node& r){
      return r+(*this);
}
Node* doubleNode::operator+(  doubleNode& r){
  dbg("double class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* doubleNode::operator+(  intNode& r){
  dbg("double class doing int addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}

Node* doubleNode::operator-(  Node& r){
      return r-(*this);
}
Node* doubleNode::operator-(  doubleNode& r){
  dbg("double class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
Node* doubleNode::operator-(  intNode& r){
  dbg("double class doing int subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}

Node* doubleNode::operator/(  Node& r){
      return r/(*this);
}
Node* doubleNode::operator/(  doubleNode& r){
  dbg("double class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
Node* doubleNode::operator/(  intNode& r){
  dbg("double class doing int division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}

Node* doubleNode::operator*(  Node& r){
      return r*(*this);
}
Node* doubleNode::operator*(  doubleNode& r){
  dbg("double class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
Node* doubleNode::operator*(  intNode& r){
  dbg("double class doing int multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}

bool doubleNode::operator==(  Node& r){
      return r==(*this);
}
bool doubleNode::operator==(  doubleNode& r){
  dbg("double node comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool doubleNode::operator==(  intNode& r){
  dbg("double node comparing int node"<<std::endl);
  return getValue()==r.getValue();
}

