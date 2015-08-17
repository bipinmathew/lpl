#include "node.h"
divNode::divNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
Node* divNode::clone(){return new divNode(*this);}
void divNode::accept(Visitor* _v){_v->visit(this);}
