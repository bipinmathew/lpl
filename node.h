#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

  template <class T> class TerminalNode;

  class Node {
    public:
        virtual TerminalNode<double>* eval();
                template <class T> TerminalNode<T>* evalLeft();
                template <class T> TerminalNode<T>* evalRight();
        void setLeft(Node* left);
        void setRight(Node* right);
        Node(const std::string& input, Node *l,Node *r);
        Node(){};
    private:
        std::string op;
        Node *l, *r;
  };

  template <class T>
  class TerminalNode : public Node {
      public:
          virtual TerminalNode<T>* eval();
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
  TerminalNode<T>::TerminalNode(T value){
      std::cout << value << std::endl;
      setValue(value);
  }


  template <class T>
  void TerminalNode<T>::setValue(T value){
      v=value;
  }


  template <class T>
  TerminalNode<T>* TerminalNode<T>::eval(){
      return this;
  }

#endif
