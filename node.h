#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>
  template <class T> class Result {};

  class Node {
    public:
        // virtual Result <class T> * eval();
        // Result <class> * evalLeft();
        // Result <class> evalRight();
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
          virtual T eval();
          void setValue(T value);
          TerminalNode(T value);
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
    T TerminalNode<T>::eval(){
        return(v);
    }
#endif
