#include "node.h"
#include <iostream>
#include "debug.h"

addNode::addNode(Node *_l, Node *_r){dbg("  addNode left-right constructor."<<std::endl;);addChild(_l);addChild(_r);}

void addNode::_print() const {dbg("I am an add node."<<std::endl);}
Node* addNode::clone() const {return new addNode(*this);}
void addNode::accept(Visitor* _v) const {_v->visit(this);}

