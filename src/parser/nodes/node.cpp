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

Node* Node::operator+( const Node& r ) const {
    return r.add(*this);
}

Node* Node::add( const Node& r) const {
    dbg("this seems like an error."<<std::endl);
    return r.add(*this);
}
Node* Node::add( const doubleNode& r) const {
    dbg("this seems like an error."<<std::endl);
    return r.add(*this);
}
Node* Node::add( const intNode& r) const {
    dbg("this seems like an error."<<std::endl);
    return r.add(*this);
}

Node* Node::operator-( const Node& r ) const   {
      throw syntaxError();
    }
Node* Node::operator-( const doubleNode& r ) const {
    return r-(*this);
}
 Node* Node::operator-( const intNode& r ) const   {
    return r-(*this);
}

Node* Node::operator/( const Node& r ) const   {
      throw syntaxError();
    }
Node* Node::operator/( const doubleNode& r ) const {
    return r/(*this);
}
 Node* Node::operator/( const intNode& r ) const   {
    return r/(*this);
}

Node* Node::operator*( const Node& r ) const   {
      throw syntaxError();
    }
Node* Node::operator*( const doubleNode& r ) const {
    return r*(*this);
}
 Node* Node::operator*( const intNode& r ) const   {
    return r*(*this);
}

bool Node::operator==( const Node& r) const  {
  throw syntaxError();
}
bool Node::operator==( const doubleNode& r) const {
    dbg("generic node doing double comparison."<<std::endl;);
    return r==(*this);
}
bool Node::operator==( const intNode& r) const {
    return r==(*this);
}


std::ostream& Node::print (std::ostream& rhs) const {return rhs << "generic node."; }
