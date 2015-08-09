#include "node.h"

doubleNode::doubleNode(){}
doubleNode::doubleNode(double value) : elementaryNode<double> (value){}
void doubleNode::accept(Visitor* _v){_v->visit(this);}
void doubleNode::identify(){std::cout<<"I am a double node."<<std::endl;}

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

