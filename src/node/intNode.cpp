#include "node.h"


intNode::intNode(){}
intNode::intNode(int value) : elementaryNode<int> (value){}
void intNode::accept(Visitor* _v){_v->visit(this);}
void intNode::identify(){std::cout<<"I am a int node."<<std::endl;}


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

