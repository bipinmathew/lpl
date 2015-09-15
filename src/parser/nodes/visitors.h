#ifndef __VISITORS__H
#define __VISITORS__H
#include <stack>
#include "node.h"
class Visitor {
  public:
    virtual void visit(const Node *_elm)=0;
    virtual void visit(const intNode *_elm)=0;
    virtual void visit(const doubleNode *_elm)=0;
    virtual void visit(const addNode *_elm)=0;
    virtual void visit(const subNode *_elm)=0;
    virtual void visit(const divNode *_elm)=0;
    virtual void visit(const multNode *_elm)=0;
};

class evalVisitor : public Visitor {
  public:
    virtual void visit(const Node *_elm);
    virtual void visit(const intNode *_elm);
    virtual void visit(const doubleNode *_elm);
    virtual void visit(const addNode *_elm);
    virtual void visit(const subNode *_elm);
    virtual void visit(const divNode *_elm);
    virtual void visit(const multNode *_elm);
    const terminalNode* getTop() const;
    void cleanup();
  private:
    std::stack <const terminalNode*> S;
    std::stack <const terminalNode*> T;
};

#endif
