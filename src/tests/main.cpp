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
  a.setLeft(&d);
  a.setRight(&i);

  i.accept(&v);
  d.accept(&v);
  a.accept(&v);
}
