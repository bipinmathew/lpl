#include "node.h"
#include <iostream>
#include <string>
#include "debug.h"

intNode::intNode(int value) : elementaryNode<int> (value){dbg("  intNode int constructor."<<std::endl);}
void intNode::accept(Visitor* _v) const {_v->visit(this);}
void intNode::_print() const {dbg("I am a int node."<<std::endl);}


std::ostream& intNode::print(std::ostream& os) const {
  return os << getValue();
}


terminalNode* intNode::clone() const {return new intNode(*this);}

terminalNode* intNode::_add( const terminalNode& r) const {
  dbg("  Determining RHS Type:"<<std::endl);
  return r._add(*this);
}
terminalNode* intNode::_add( const doubleNode& r) const{
  dbg("int class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
terminalNode* intNode::_add( const intNode& r) const{
  dbg("int class doing int addition"<<std::endl);
  return new intNode(getValue()+r.getValue());
}


terminalNode* intNode::_sub( const terminalNode& r) const {
  dbg("  Determining RHS Type:"<<std::endl);
  return r._sub(*this);
}
terminalNode* intNode::_sub( const doubleNode& r) const{
  dbg("intNode+doubleNode: ("<<getValue()<< " - "<<r.getValue()<<" = )"<<std::endl);
  return new doubleNode(getValue()-r.getValue());
}
terminalNode* intNode::_sub( const intNode& r) const{
  dbg("intNode+intNode: ("<<getValue()<< " - "<<r.getValue()<<" = )"<<std::endl);
  return new intNode(getValue()-r.getValue());
}

terminalNode* intNode::_div( const terminalNode& r ) const {
  dbg("  Determining RHS Type:"<<std::endl);
  return r._div(*this);
}
terminalNode* intNode::_div( const doubleNode& r ) const {
  dbg("int class doing double division"<<std::endl);
  if(r.getValue()==0)
      throw divByZeroError();
  else
    return new doubleNode(getValue()/r.getValue());
}
terminalNode* intNode::_div( const intNode& r ) const {
  dbg("int class doing int division"<<std::endl);
  if(r.getValue()==0)
      throw divByZeroError();
  else
      return new doubleNode(((double)getValue())/((double)r.getValue()));
}

terminalNode* intNode::_mult( const terminalNode& r ) const {
  dbg("  Determining RHS Type:"<<std::endl);
  return r._mult(*this);
}
terminalNode* intNode::_mult( const doubleNode& r ) const {
  dbg("int class doing double multiplication"<<std::endl);
  return new doubleNode(getValue()*r.getValue());
}
terminalNode* intNode::_mult( const intNode& r ) const {
  dbg("int class doing int multiplication"<<std::endl);
  return new intNode(getValue()*r.getValue());
}

terminalNode* intNode::_negate() const {
  dbg("int class doing negation"<<std::endl);
  return new intNode(-getValue());
}


terminalNode* intNode::_bang() const {
  dbg("int class doing bang"<<std::endl);
  int numElements;
  int v(getValue());
  numElements = 1+(v>=0 ? v : -v);
  int *p = new int[numElements];
  for(int i=0;i<numElements;i++)
    p[i]=i;
  return new intArrayNode(p);
}


bool intNode::eq(   const terminalNode& r) const {
  dbg("  Determining RHS Type:"<<std::endl);
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
