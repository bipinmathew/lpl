#include "node.h"
#include "visitors.h"

const Node* evalVisitor::getTop(){return S.top();}
void evalVisitor::visit(const Node *_elm){dbg("Visited a generic."<<std::endl);}
void evalVisitor::visit(const doubleNode *_elm){dbg("Visited a double."<<std::endl); S.push(_elm);}
void evalVisitor::visit(const intNode *_elm){dbg("Visited a int."<<std::endl); S.push(_elm);}
void evalVisitor::visit(const addNode *_elm){
  dbg("Visit addNode." << std::endl);
  const Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)+(*r));
}


void evalVisitor::visit(const subNode *_elm){
  dbg("Visit subNode." << std::endl);
  const Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)-(*r));
}

void evalVisitor::visit(const divNode *_elm){
  dbg("Visit divNode." << std::endl);
  const Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)/(*r));
}

void evalVisitor::visit(const multNode *_elm){
  dbg("Visit multNode." << std::endl);
  const Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)*(*r));
}
