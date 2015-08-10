#include "node.h"
multNode::multNode(Node *_l, Node *_r){setLeft(_l);setRight(_r);}
void multNode::accept(Visitor* _v){_v->visit(this);}
