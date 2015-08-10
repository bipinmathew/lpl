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
    void visit(Node *_elm);
    void visit(intNode *_elm);
    void visit(doubleNode *_elm);
    void visit(addNode *_elm);
    void visit(subNode *_elm);
    void visit(divNode *_elm);
    void visit(multNode *_elm);
  private:
    std::stack <Node*> S;
};
#endif
