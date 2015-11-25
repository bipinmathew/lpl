#include "node.h"
negNode::negNode(Node *_l){addChild(_l);}
Node* negNode::clone() const {return new negNode(*this);}
void negNode::accept(Visitor* _v) const {_v->visit(this);}
void negNode::_print() const {dbg("I am a negNode."<<std::endl);}
