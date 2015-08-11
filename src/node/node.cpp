#include "node.h"
#include <iostream>
#include "debug.h"

Node::Node(){dbg("  Node constructor."<<std::endl;);l=NULL;r=NULL;}
void Node::setLeft(Node *_l){l = _l;}
void Node::setRight(Node *_r){r = _r;}
Node* Node::getLeft(){return l;}
Node* Node::getRight(){return r;}
void Node::identify(){std::cout<<"I am a generic node."<<std::endl;}
Node* Node::operator+(   Node& r)  {
      return new errorNode("node+node error.");
    }
Node* Node::operator+(  doubleNode& r){
    return r+(*this);
}
 Node* Node::operator+(   intNode& r)  {
    return r+(*this);
}

Node* Node::operator-(   Node& r)  {
      return new errorNode("node-node error.");
    }
Node* Node::operator-(  doubleNode& r){
    return r-(*this);
}
 Node* Node::operator-(   intNode& r)  {
    return r-(*this);
}

Node* Node::operator/(   Node& r)  {
      return new errorNode("node/node error.");
    }
Node* Node::operator/(  doubleNode& r){
    return r/(*this);
}
 Node* Node::operator/(   intNode& r)  {
    return r/(*this);
}

Node* Node::operator*(   Node& r)  {
      return new errorNode("node*node error.");
    }
Node* Node::operator*(  doubleNode& r){
    return r*(*this);
}
 Node* Node::operator*(   intNode& r)  {
    return r*(*this);
}

bool Node::operator==(   Node& r)  {
      return false; // this should be an error.
}
bool Node::operator==(  doubleNode& r){
    return r==(*this);
}
bool Node::operator==(   intNode& r)  {
    return r==(*this);
}
