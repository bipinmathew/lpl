#include "node.h"
#include <iostream>
#include <vector>
#include "debug.h"

Node::~Node(){
  for(std::vector<Node*>::const_iterator it = children.begin(); it!=children.end();++it){
    if((*it)!=NULL){
      delete *it;
    }
  }
}
void Node::addChild(Node *_c){children.push_back(_c);}

void Node::_print() const {dbg("I am a generic node."<<std::endl);}

terminalNode* operator+( const terminalNode& l,  const terminalNode& r ) {
    dbg("Dispatching add function..."<<std::endl;);
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

terminalNode* negate( const terminalNode& l) {
    return l.neg();
}


bool operator==( const terminalNode& l, const terminalNode& r) {
    return l.eq(r);
}
std::ostream& Node::print (std::ostream& rhs) const {return rhs << "generic node."; }
