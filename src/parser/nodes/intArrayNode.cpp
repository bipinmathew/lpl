#include "node.h"
#include <iostream>
#include <string>
#include "debug.h"

void intArrayNode::accept(Visitor* _v) const {_v->visit(this);}
intArrayNode::intArrayNode(int *_v) : elementaryNode<int*> (_v) {dbg("  intArrayNode constructor"<<std::endl;); }


void intArrayNode::_print() const {dbg("I am a int node."<<std::endl);}
std::ostream& intArrayNode::print(std::ostream& os) const {
    int *p;
    p = getValue();
  return os << p[0];
}
