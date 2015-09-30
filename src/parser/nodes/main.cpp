#include "node.h"
#include "visitors.h"


int main(){
  doubleNode d;
  intNode i;
  addNode a;
  evalVisitor v;
  Node *t;

  d.setValue(3.8);
  i.setValue(8);
  a.addChild(&d);
  a.addChild(&i);

  v.visit(&a);

}
