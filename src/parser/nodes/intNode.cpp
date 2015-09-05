#include "node.h"
#include <iostream>
#include "debug.h"

intNode::intNode(int value) : elementaryNode<int> (value){dbg("intNode int constructor."<<std::endl);}
void intNode::accept(Visitor* _v) const {_v->visit(this);}
void intNode::identify() const {std::cout<<"I am a int node."<<std::endl;}
Node* intNode::clone() const {return new intNode(*this);}


Node* intNode::operator+( const Node& r) const{
      return r+(*this);
}
Node* intNode::operator+( const doubleNode& r) const{
  dbg("int class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* intNode::operator+( const intNode& r) const{
  dbg("int class doing int addition"<<std::endl);
  return new intNode(getValue()+r.getValue());
}

Node* intNode::operator-( const Node& r ) const {
      return r-(*this);
}
Node* intNode::operator-( const doubleNode& r ) const {
  dbg("int class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
Node* intNode::operator-( const intNode& r ) const {
  dbg("int class doing int subtraction"<<std::endl);
  return new intNode(getValue()-r.getValue());
}

Node* intNode::operator/( const Node& r ) const {
      return r/(*this);
}
Node* intNode::operator/( const doubleNode& r ) const {
  dbg("int class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
Node* intNode::operator/( const intNode& r ) const {
  dbg("int class doing int division"<<std::endl);
  if(r.getValue()==0)
      throw divByZeroError();
  else
      return new intNode(getValue()/r.getValue());
}

Node* intNode::operator*( const Node& r ) const {
      return r*(*this);
}
Node* intNode::operator*( const doubleNode& r ) const {
  dbg("int class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
Node* intNode::operator*( const intNode& r ) const {
  dbg("int class doing int multiplication"<<std::endl);
  return new intNode(getValue()*r.getValue());
}

bool intNode::operator==(   const Node& r) const {
      return r==(*this);
}
bool intNode::operator==(   const doubleNode& r) const {
  dbg("int comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool intNode::operator==(   const intNode& r) const {
  dbg("int comparing int node"<<std::endl);
  return getValue()==r.getValue();
}

