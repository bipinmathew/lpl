#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

class Visitor;

class Node {
  public:
    void setLeft(Node* left);
    void setRight(Node* right);
    Node* getLeft();
    Node* getRight();
    Node(Node *l,Node *r);
    Node();
    virtual void accept (Visitor* v);
  private:
    Node *l, *r;
};



class OpNode : public Node{
  public:
    OpNode(const std::string& input, Node* left, Node*right);
    void setOp(const std::string& input);
    virtual void accept(Visitor* v);
  private:
    std::string op;
};

template <class T>
class TerminalNode : public Node {
  public:
      void setValue(T value);
      TerminalNode(T value);
      virtual void accept(Visitor* v);
  private:
      T v;
};


template <class T>
TerminalNode<T>::TerminalNode(T value) : Node() {
  std::cout << value << std::endl;
  setValue(value);
}


template <class T>
void TerminalNode<T>::setValue(T value) {
  v=value;
}


class Visitor {
  public:
    virtual void visit(Node* n) = 0;
    virtual void visit(OpNode* n) = 0;
    virtual void visit(TerminalNode<double>* n) = 0;
    virtual void visit(TerminalNode<int>* n) = 0;
};

class EvalVisitor : public Visitor {
  public:
    virtual void visit(Node* n);
    virtual void visit(OpNode* n);
    template <class T>
    void visit(TerminalNode<T>* n);
    virtual void visit(TerminalNode<double>* n);
    virtual void visit(TerminalNode<int>* n);
};



#endif
