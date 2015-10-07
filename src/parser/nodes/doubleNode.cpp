#include "node.h"
#include <iostream>
#include "debug.h"

doubleNode::doubleNode(double value) : elementaryNode<double> (value){dbg("doubleNode double constructor."<<std::endl);}
void doubleNode::accept(Visitor* _v) const {_v->visit(this);}
void doubleNode::_print() const {dbg("I am a double node."<<std::endl);}



std::ostream& doubleNode::print(std::ostream& os) const {
  return os << getValue();
}

terminalNode* doubleNode::clone() const {return new doubleNode(*this);}


terminalNode* doubleNode::_add( const terminalNode& r) const {
  dbg("double class doing double addition"<<std::endl);
  return r._add(*this);
}

terminalNode* doubleNode::_add( const doubleNode& r) const {
  dbg("double class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
terminalNode* doubleNode::_add( const intNode& r) const {
  dbg("double class doing int addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}



terminalNode* doubleNode::_sub( const terminalNode& r) const {
  dbg("double class doing double subtraction"<<std::endl);
  return r._sub(*this);
}

terminalNode* doubleNode::_sub( const doubleNode& r) const {
  dbg("double class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
terminalNode* doubleNode::_sub( const intNode& r) const {
  dbg("double class doing int subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}

terminalNode* doubleNode::_div( const terminalNode& r ) const {
  dbg("this should be syntax error."<<std::endl);
  return r._div(*this);
}
terminalNode* doubleNode::_div( const doubleNode& r ) const {
  dbg("double class doing double division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}
terminalNode* doubleNode::_div( const intNode& r ) const {
  dbg("double class doing int division"<<std::endl);
  return new doubleNode(getValue()/r.getValue());
}

terminalNode* doubleNode::_mult( const terminalNode& r ) const {
      return r._mult(*this);
}
terminalNode* doubleNode::_mult( const doubleNode& r ) const {
  dbg("double class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
terminalNode* doubleNode::_mult( const intNode& r ) const {
  dbg("double class doing int multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}

terminalNode* doubleNode::_negate() const {
  dbg("int class doing negation"<<std::endl);
  return new doubleNode(-getValue());
}

terminalNode* doubleNode::_bang() const {
  dbg("int class doing negation"<<std::endl);
  return new doubleNode(-getValue());
}

bool doubleNode::eq(  const terminalNode& r) const {
      dbg("double node comparing generic node"<<std::endl);
      return r.eq(*this);
}
bool doubleNode::eq(  const doubleNode& r) const {
  dbg("double node comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool doubleNode::eq(  const intNode& r) const {
  dbg("double node comparing int node"<<std::endl);
  return getValue()==r.getValue();
}

