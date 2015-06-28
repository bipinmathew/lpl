#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>
#include <stack>

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
    virtual Node* operator+(const Node& rhs){std::cout << "This is a parsing error." << std::endl;}; 
  private:
    Node *l, *r;
};



class OpNode : public Node{
  public:
    OpNode(const std::string& input, Node* left, Node*right);
    void setOp(const std::string& input);
    std::string& getOp(){return op;}
    virtual void accept(Visitor* v);
  private:
    std::string op;
};

template <class T>
class TerminalNode : public Node {
  public:
      void setValue(T value);
      TerminalNode(T value);
      virtual void accept(Visitor* v) = 0;
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




class doubleNode : public TerminalNode<double>{
  public:
    doubleNode(double value) : TerminalNode<double>(value){};
    virtual void accept(Visitor* v);
};


class intNode : public TerminalNode<int>{
  public:
    intNode(int value) : TerminalNode<int>(value){};
    virtual Node* operator+(const Node& rhs){std::cout << "INT." << std::endl;}; 
    //Node operator+(const intNode& other){std::cout << "int node addition!" << std::endl;}; 
    virtual void accept(Visitor* v);
};


class Visitor {
  public:
    virtual void visit(Node* n) = 0;
    virtual void visit(OpNode* n) = 0;
    virtual void visit(doubleNode* n) = 0;
    virtual void visit(intNode* n) = 0;
};

class EvalVisitor : public Visitor {
  public:
    virtual void visit(Node* n);
    virtual void visit(OpNode* n);
    template <class T>
    void visit(TerminalNode<T>* n);
    virtual void visit(doubleNode* n);
    virtual void visit(intNode* n);
    std::stack<Node*> S;
  private:
};



#endif
