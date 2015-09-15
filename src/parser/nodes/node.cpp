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
    return this->div(r);
}

terminalNode* terminalNode::operator*( const terminalNode& r ) const   {
    return this->mult(r);
}

bool terminalNode::operator==( const terminalNode& r) const  {
    return this->eq(r);
}
std::ostream& Node::print (std::ostream& rhs) const {return rhs << "generic node."; }
