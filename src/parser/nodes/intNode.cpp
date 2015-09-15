#include "node.h"
#include <iostream>
#include <string>
#include "debug.h"

intNode::intNode(int value) : elementaryNode<int> (value){dbg("intNode int constructor."<<std::endl);}
void intNode::accept(Visitor* _v) const {_v->visit(this);}
void intNode::identify() const {dbg("I am a int node."<<std::endl);}


std::ostream& intNode::print(std::ostream& os) const {
  return os << getValue();
}


terminalNode* intNode::clone() const {return new intNode(*this);}

terminalNode* intNode::add( const terminalNode& r) const {
  dbg("this should be syntax error."<<std::endl);
  return r.add(*this);
}
terminalNode* intNode::add( const doubleNode& r) const{
  dbg("int class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
terminalNode* intNode::add( const intNode& r) const{
  dbg("int class doing int addition"<<std::endl);
  return new intNode(getValue()+r.getValue());
}


terminalNode* intNode::sub( const terminalNode& r) const {
  dbg("this should be syntax error."<<std::endl);
  return r.sub(*this);
}
terminalNode* intNode::sub( const doubleNode& r) const{
  dbg("int class doing double subtraction"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
terminalNode* intNode::sub( const intNode& r) const{
  dbg("int class doing int subtraction"<<std::endl);
  return new intNode(getValue()-r.getValue());
}

terminalNode* intNode::div( const terminalNode& r ) const {
  dbg("this should be syntax (int) error."<<std::endl);
  return r.div(*this);
}
terminalNode* intNode::div( const doubleNode& r ) const {
  dbg("int class doing double division"<<std::endl);
  if(r.getValue()==0)
      throw divByZeroError();
  else
    return new doubleNode(getValue()/r.getValue());
}
terminalNode* intNode::div( const intNode& r ) const {
  dbg("int class doing int division"<<std::endl);
  if(r.getValue()==0)
      throw divByZeroError();
  else
      return new doubleNode(((double)getValue())/((double)r.getValue()));
}

terminalNode* intNode::mult( const terminalNode& r ) const {
      return r.mult(*this);
}
terminalNode* intNode::mult( const doubleNode& r ) const {
  dbg("int class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
terminalNode* intNode::mult( const intNode& r ) const {
  dbg("int class doing int multiplication"<<std::endl);
  return new intNode(getValue()*r.getValue());
}

bool intNode::eq(   const terminalNode& r) const {
      return r.eq(*this);
}
bool intNode::eq(   const doubleNode& r) const {
  dbg("int comparing double node"<<std::endl);
  return getValue()==r.getValue();
}
bool intNode::eq(   const intNode& r) const {
  dbg("int comparing int node"<<std::endl);
  return getValue()==r.getValue();
}
