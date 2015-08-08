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
};

class evalVisitor : public Visitor {
  public:
    void visit(Node *_elm);
    void visit(intNode *_elm);
    void visit(doubleNode *_elm);
    void visit(addNode *_elm);
  private:
    std::stack <Node*> S;
};
#endif
