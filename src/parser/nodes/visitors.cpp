#include "node.h"
#include "visitors.h"

const terminalNode* evalVisitor::getTop() const {return S.top();}

evalVisitor::~evalVisitor(){
  cleanup();
}

void evalVisitor::cleanup(){
  const Node *l;
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

bool evalVisitor::getDyadicArgs(const terminalNode** l, const terminalNode** r){
  if(S.size() < 2){
    throw unexpectedNumArgsError();
  }
  T.push(*l = S.top());
  S.pop();

  T.push(*r = S.top());
  S.pop();
  return 0;
}

void evalVisitor::eval(const Node *root){
  for(std::vector<Node*>::const_iterator it = root->children.begin(); it!=root->children.end();++it){
    if((*it)!=NULL){
      eval(*it);
    }
  }
  root->acceptVisitor(this);
}

void evalVisitor::visit(const Node *_elm){dbg("Visited a generic."<<std::endl);}
void evalVisitor::visit(const doubleNode *_elm){dbg("Visited a double."<<std::endl); S.push(_elm->clone());}
void evalVisitor::visit(const intNode *_elm){dbg("Visited a int."<<std::endl); S.push(_elm->clone());}
void evalVisitor::visit(const addNode *_elm){
  dbg("Visit addNode." << std::endl);
  const terminalNode *l, *r;
  getDyadicArgs(&l,&r);

  S.push((*l)+(*r));
}


void evalVisitor::visit(const subNode *_elm){
  dbg("Visit subNode." << std::endl);
  const terminalNode *l, *r;
  getDyadicArgs(&l,&r);

  S.push((*l)-(*r));
}

void evalVisitor::visit(const divNode *_elm){
  dbg("Visit divNode." << std::endl);
  const terminalNode *l, *r;
  getDyadicArgs(&l,&r);

  S.push((*l)/(*r));
}

void evalVisitor::visit(const multNode *_elm){
  dbg("Visit multNode." << std::endl);
  const terminalNode *l, *r;
  getDyadicArgs(&l,&r);

  S.push((*l)*(*r));
}

