#include "node.h"
#include <iostream>
#include "debug.h"

doubleNode::doubleNode(double value) : elementaryNode<double> (value){dbg("doubleNode double constructor."<<std::endl);}
void doubleNode::accept(Visitor* _v) const {_v->visit(this);}
void doubleNode::identify() const {dbg("I am a double node."<<std::endl);}



std::ostream& doubleNode::print(std::ostream& os) const {
  return os << getValue();
}

terminalNode* doubleNode::clone() const {return new doubleNode(*this);}


terminalNode* doubleNode::add( const terminalNode& r) const {
  dbg("double class doing double addition"<<std::endl);
  return r.add(*this);
}

terminalNode* doubleNode::add( const doubleNode& r) const {
  dbg("double class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
terminalNode* doubleNode::add( const intNode& r) const {
  dbg("double class doing int addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}



terminalNode* doubleNode::sub( const terminalNode& r) const {
  dbg("double class doing double subtraction"<<std::endl);
  return r.sub(*this);
}

terminalNode* doubleNode::sub( const doubleNode& r) const {
  dbg("double class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
terminalNode* doubleNode::sub( const intNode& r) const {
  dbg("double class doing int subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}


terminalNode* doubleNode::operator/( const terminalNode& r ) const {
      return r/(*this);
}
terminalNode* doubleNode::operator/( const doubleNode& r ) const {
  dbg("double class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
terminalNode* doubleNode::operator/( const intNode& r ) const {
  dbg("double class doing int division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}

terminalNode* doubleNode::operator*( const terminalNode& r ) const {
      return r*(*this);
}
terminalNode* doubleNode::operator*( const doubleNode& r ) const {
  dbg("double class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
terminalNode* doubleNode::operator*( const intNode& r ) const {
  dbg("double class doing int multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}

bool doubleNode::operator==(  const terminalNode& r) const {
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

