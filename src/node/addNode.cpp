#include "node.h"
#include <iostream>
#include "debug.h"

addNode::addNode(){dbg("addNode default constructor."<<std::endl);}
addNode::addNode(Node *_l, Node *_r){dbg("addNode left-right constructor."<<std::endl;);setLeft(_l);setRight(_r);}

void addNode::identify(){std::cout<<"I am an add node."<<std::endl;}
Node* addNode::clone(){return new addNode(*this);}
void addNode::accept(Visitor* _v){_v->visit(this);}
