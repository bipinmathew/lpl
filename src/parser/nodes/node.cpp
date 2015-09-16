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

terminalNode* operator+( const terminalNode& l,  const terminalNode& r ) {
    return l.add(r);
}

terminalNode* operator-( const terminalNode& l,  const terminalNode& r ) {
    return l.sub(r);
}

terminalNode* operator/( const terminalNode& l,  const terminalNode& r ) {
    return l.div(r);
}

terminalNode* operator*( const terminalNode& l,  const terminalNode& r ) {
    return l.mult(r);
}

bool operator==( const terminalNode& l, const terminalNode& r) {
    return l.eq(r);
}
std::ostream& Node::print (std::ostream& rhs) const {return rhs << "generic node."; }
