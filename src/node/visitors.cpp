#include "node.h"
#include "visitors.h"

Node* evalVisitor::getTop(){return S.top();}
void evalVisitor::cleanup(){
  Node *l;
  dbg("Unwinding stack...\n");
  while(S.size()>0){
    dbg("...pop\n");
    l = S.top();
    S.pop();
    delete l;
  }
  while(T.size()>0){
    dbg("...pop\n");
    l = T.top();
    T.pop();
    delete l;
  }
}
void evalVisitor::visit(const Node *_elm){dbg("Visited a generic."<<std::endl);}
void evalVisitor::visit(const doubleNode *_elm){dbg("Visited a double."<<std::endl); S.push(_elm->clone());}
void evalVisitor::visit(const intNode *_elm){dbg("Visited a int."<<std::endl); S.push(_elm->clone());}
void evalVisitor::visit(const addNode *_elm){
  dbg("Visit addNode." << std::endl);
  Node *l, *r;
  T.push(l = S.top());
  l->identify();
  S.pop();

  T.push(r = S.top());
  r->identify();
  S.pop();

  S.push((*l)+(*r));
}


void evalVisitor::visit(const subNode *_elm){
  dbg("Visit subNode." << std::endl);
  Node *l, *r;
  T.push(l = S.top());
  l->identify();
  S.pop();

  T.push(r = S.top());
  r->identify();
  S.pop();

  S.push((*l)-(*r));
}

void evalVisitor::visit(const divNode *_elm){
  dbg("Visit divNode." << std::endl);
  Node *l, *r;
  T.push(l = S.top());
  l->identify();
  S.pop();

  T.push(r = S.top());
  r->identify();
  S.pop();

  S.push((*l)/(*r));
}

void evalVisitor::visit(const multNode *_elm){
  dbg("Visit multNode." << std::endl);
  Node *l, *r;
  T.push(l = S.top());
  l->identify();
  S.pop();

  T.push(r = S.top());
  r->identify();
  S.pop();

  S.push((*l)*(*r));
}
