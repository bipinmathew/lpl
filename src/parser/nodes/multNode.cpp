#include "node.h"
multNode::multNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
Node* multNode::clone() const {return new multNode(*this);}
void multNode::accept(Visitor* _v) const {_v->visit(this);}
void multNode::_print() const {dbg("I am a divNode."<<std::endl);}
