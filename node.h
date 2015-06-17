#ifndef NODE_H
#define NODE_H
#include <string>
  class Node {
    public:
        virtual int eval();
        int evalLeft();
        int evalRight();
        void setLeft(Node* left);
        void setRight(Node* right);
        Node(const std::string& input, Node *l,Node *r);
        Node(){};
    private:
        std::string op;
        Node *l, *r;
  };

  class TerminalNode : public Node {
      public:
          virtual int eval();
          void setValue(int value);
          TerminalNode(int value);
      private:
          int v;
  };
#endif
