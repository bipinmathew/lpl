#include "node.h"
#include <iostream>
#include "debug.h"

addNode::addNode(Node *_l, Node *_r){dbg("addNode left-right constructor."<<std::endl;);setLeft(_l);setRight(_r);}
void addNode::accept(Visitor* _v){_v->visit(this);}
