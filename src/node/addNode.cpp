#include "node.h"
addNode::addNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
void addNode::accept(Visitor* _v){_v->visit(this);}
