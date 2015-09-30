#include "node.h"
divNode::divNode(Node *_l, Node *_r){addChild(_l);addChild(_r);}
Node* divNode::clone() const {return new divNode(*this);}
void divNode::accept(Visitor* _v) const {_v->visit(this);}
void divNode::_print() const {dbg("I am a divNode."<<std::endl);}
