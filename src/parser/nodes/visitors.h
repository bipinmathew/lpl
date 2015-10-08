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
    virtual void visit(const negNode *_elm)=0;
    virtual void visit(const bangNode *_elm)=0;
};

class evalVisitor : public Visitor {
  public:
    void eval(const Node *root);
    virtual void visit(const Node *_elm);
    virtual void visit(const intNode *_elm);
    virtual void visit(const doubleNode *_elm);
    virtual void visit(const addNode *_elm);
    virtual void visit(const subNode *_elm);
    virtual void visit(const divNode *_elm);
    virtual void visit(const multNode *_elm);
    virtual void visit(const negNode *_elm);
    virtual void visit(const bangNode *_elm);

    const terminalNode* getTop() const;
    virtual ~evalVisitor();
    void cleanup();
  private:
    bool getDyadicArgs(const terminalNode** l,const terminalNode** r);
    bool getMonadicArgs(const terminalNode** l);
    std::stack <const terminalNode*> S;
    std::stack <const terminalNode*> T;
};

#endif
