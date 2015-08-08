#include "node.h"
void addNode::accept(Visitor* _v){_v->visit(this);};
