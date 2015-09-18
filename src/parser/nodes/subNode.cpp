#include "node.h"
subNode::subNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
Node* subNode::clone() const {return new subNode(*this);}
void subNode::accept(Visitor* _v) const {_v->visit(this);}
void subNode::_print() const {dbg("I am a subNode."<<std::endl);}
