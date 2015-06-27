#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

class Node {
  public:
    void setLeft(Node* left);
    void setRight(Node* right);
    Node(Node *l,Node *r);
    Node();
  private:
    Node *l, *r;
};

class OpNode : public Node{
  public:
    OpNode(const std::string& input, Node* left, Node*right);
    void setOp(const std::string& input);
  private:
    std::string op;
};

template <class T>
class TerminalNode : public Node {
  public:
      void setValue(T value);
      TerminalNode(T value);
      TerminalNode<T>& operator+(const TerminalNode<T>& rhs){
        this.v+=rhs.v;
        return this;
      }
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

#endif
