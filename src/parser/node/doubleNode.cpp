#include "node.h"
#include <iostream>
#include "debug.h"

doubleNode::doubleNode(double value) : elementaryNode<double> (value){dbg("doubleNode double constructor."<<std::endl);}
void doubleNode::accept(Visitor* _v) const {_v->visit(this);}
void doubleNode::identify() const {std::cout<<"I am a double node."<<std::endl;}
Node* doubleNode::clone() const {return new doubleNode(*this);}

Node* doubleNode::operator+( const Node& r) const {
      return r+(*this);
}
Node* doubleNode::operator+( const doubleNode& r) const {
  dbg("double class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* doubleNode::operator+( const intNode& r) const {
  dbg("double class doing int addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}

Node* doubleNode::operator-( const Node& r ) const {
      return r-(*this);
}
Node* doubleNode::operator-( const doubleNode& r ) const {
  dbg("double class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
Node* doubleNode::operator-( const intNode& r ) const {
  dbg("double class doing int subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}

Node* doubleNode::operator/( const Node& r ) const {
      return r/(*this);
}
Node* doubleNode::operator/( const doubleNode& r ) const {
  dbg("double class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
Node* doubleNode::operator/( const intNode& r ) const {
  dbg("double class doing int division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}

Node* doubleNode::operator*( const Node& r ) const {
      return r*(*this);
}
Node* doubleNode::operator*( const doubleNode& r ) const {
  dbg("double class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
Node* doubleNode::operator*( const intNode& r ) const {
  dbg("double class doing int multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}

bool doubleNode::operator==(  const Node& r) const {
      dbg("double node comparing generic node"<<std::endl);
      return r==(*this);
}
bool doubleNode::operator==(  const doubleNode& r) const {
  dbg("double node comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool doubleNode::operator==(  const intNode& r) const {
  dbg("double node comparing int node"<<std::endl);
  return getValue()==r.getValue();
}

