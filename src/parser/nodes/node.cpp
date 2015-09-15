#include "node.h"
#include <iostream>
#include "debug.h"

Node::Node(){dbg("  Node constructor."<<std::endl;);l=NULL;r=NULL;}
Node::~Node(){
  dbg("  Node base destructor."<<std::endl;);
  if(getLeft()!=NULL){
    delete getLeft();
  }
  if(getRight()!=NULL){
    delete getRight();
  }
}
void Node::setLeft(Node *_l){l = _l;}
void Node::setRight(Node *_r){r = _r;}

Node* Node::getLeft() const {return l;}
Node* Node::getRight() const {return r;}


void Node::identify() const {dbg("I am a generic node."<<std::endl);}

terminalNode* terminalNode::operator+( const terminalNode& r ) const {
    return this->add(r);
}


terminalNode* terminalNode::operator-( const terminalNode& r ) const {
    return this->sub(r);
}


terminalNode* terminalNode::operator/( const terminalNode& r ) const   {
      throw syntaxError();
    }
terminalNode* terminalNode::operator/( const doubleNode& r ) const {
    return r/(*this);
}
terminalNode* terminalNode::operator/( const intNode& r ) const   {
    return r/(*this);
}

terminalNode* terminalNode::operator*( const terminalNode& r ) const   {
      throw syntaxError();
    }
terminalNode* terminalNode::operator*( const doubleNode& r ) const {
    return r*(*this);
}
terminalNode* terminalNode::operator*( const intNode& r ) const   {
    return r*(*this);
}

bool terminalNode::operator==( const terminalNode& r) const  {
  throw syntaxError();
}
bool terminalNode::operator==( const doubleNode& r) const {
    dbg("generic node doing double comparison."<<std::endl;);
    return r==(*this);
}
bool terminalNode::operator==( const intNode& r) const {
    return r==(*this);
}


std::ostream& Node::print (std::ostream& rhs) const {return rhs << "generic node."; }
