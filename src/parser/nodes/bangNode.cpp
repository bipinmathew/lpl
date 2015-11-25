#include "node.h"
#include <iostream>
#include "debug.h"

bangNode::bangNode(Node *_l){dbg("  bangNode constructor."<<std::endl;);addChild(_l);}

void bangNode::_print() const {dbg("I am a bang node."<<std::endl);}
Node* bangNode::clone() const {return new bangNode(*this);}
void bangNode::accept(Visitor* _v) const {_v->visit(this);}

