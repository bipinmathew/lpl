#ifndef __VISITORS__H
#define __VISITORS__H
#include <stack>
#include "node.h"
class Visitor {
  public:
    virtual void visit(Node *_elm)=0;
    virtual void visit(intNode *_elm)=0;
    virtual void visit(doubleNode *_elm)=0;
    virtual void visit(addNode *_elm)=0;
    virtual void visit(subNode *_elm)=0;
    virtual void visit(divNode *_elm)=0;
    virtual void visit(multNode *_elm)=0;
};

class evalVisitor : public Visitor {
  public:
    virtual void visit(Node *_elm);
    virtual void visit(intNode *_elm);
    virtual void visit(doubleNode *_elm);
    virtual void visit(addNode *_elm);
    virtual void visit(subNode *_elm);
    virtual void visit(divNode *_elm);
    virtual void visit(multNode *_elm);
  private:
    std::stack <Node*> S;
};
#endif
