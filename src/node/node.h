#ifndef __NODE__H
#define __NODE__H

#include <stdio.h>
#include <iostream>

class Node;
class doubleNode;
class intNode;
class addNode;
class subNode;
class divNode;
class multNode;
class errorNode;
#define DEBUG_BUILD
#include "visitors.h"
#include "debug.h"


class Node{
  public:
    Node();
    virtual void setLeft(Node *_l);
    virtual void setRight(Node *_r);
    virtual Node* getLeft();
    virtual Node* getRight();
    virtual void identify();
    virtual void accept(Visitor* _v) = 0;

    virtual Node* operator+(   Node& r) ;
    virtual Node* operator+(   intNode& r) ;
    virtual Node* operator+(  doubleNode& r);

    virtual Node* operator-(   Node& r) ;
    virtual Node* operator-(   intNode& r) ;
    virtual Node* operator-(  doubleNode& r);

    virtual Node* operator/(   Node& r) ;
    virtual Node* operator/(   intNode& r) ;
    virtual Node* operator/(  doubleNode& r);

    virtual Node* operator*(   Node& r) ;
    virtual Node* operator*(   intNode& r) ;
    virtual Node* operator*(  doubleNode& r);

    virtual bool operator==(   Node& r) ;
    virtual bool operator==(   intNode& r) ;
    virtual bool operator==(  doubleNode& r);
  private:
    Node *l,*r;
};

template <class T>
class elementaryNode : public Node{
  public:
    virtual T getValue() {return value;};
    virtual void setValue(T _value) {value = _value;};
    elementaryNode(T _v) {setValue(_v);};
    elementaryNode(){};
  private:
    T value;
};

class intNode : public elementaryNode<int> {
  public:
    intNode();
    intNode(int value);
    virtual void accept(Visitor* _v);
     virtual void identify();
     virtual Node* operator+(   Node& r) ;
     virtual Node* operator+(   doubleNode& r) ;
     virtual Node* operator+(   intNode& r) ;


     virtual Node* operator-(   Node& r) ;
     virtual Node* operator-(   doubleNode& r) ;
     virtual Node* operator-(   intNode& r) ;

    virtual Node* operator/(   Node& r) ;
    virtual Node* operator/(   intNode& r) ;
    virtual Node* operator/(  doubleNode& r);

    virtual Node* operator*(   Node& r) ;
    virtual Node* operator*(   intNode& r) ;
    virtual Node* operator*(  doubleNode& r);

    virtual bool operator==(   Node& r) ;
    virtual bool operator==(   intNode& r) ;
    virtual bool operator==(  doubleNode& r);
};


class doubleNode : public elementaryNode<double> {
  public:
    doubleNode();
    doubleNode(double value);
    virtual void accept(Visitor* _v);
    virtual void identify();
    virtual Node* operator+(  Node& r);
    virtual Node* operator+(  intNode& r);
    virtual Node* operator+(  doubleNode& r);

    virtual Node* operator-(   Node& r) ;
    virtual Node* operator-(   doubleNode& r) ;
    virtual Node* operator-(   intNode& r) ;

    virtual Node* operator/(   Node& r) ;
    virtual Node* operator/(   intNode& r) ;
    virtual Node* operator/(  doubleNode& r);

    virtual Node* operator*(   Node& r) ;
    virtual Node* operator*(   intNode& r) ;
    virtual Node* operator*(  doubleNode& r);

    virtual bool operator==(   Node& r) ;
    virtual bool operator==(   intNode& r) ;
    virtual bool operator==(  doubleNode& r);
};


class errorNode : public elementaryNode<std::string>{
  public:
    errorNode( std::string s );
    virtual void accept( Visitor *_v);
};


class addNode : public Node {
  public:
    addNode(Node *_l, Node *_r);
    virtual void accept(Visitor* _v);
};

class subNode : public Node {
  public:
    subNode(Node *_l, Node *_r);
    virtual void accept(Visitor* _v);
};

class divNode : public Node {
  public:
    divNode(Node *_l, Node *_r);
    virtual void accept(Visitor* _v);
};

class multNode : public Node {
  public:
    multNode(Node *_l, Node *_r);
    virtual void accept(Visitor* _v);
};

#endif
