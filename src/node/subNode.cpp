#include "node.h"
subNode::subNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
Node* subNode::clone(){return new subNode(*this);}
void subNode::accept(Visitor* _v){_v->visit(this);}
