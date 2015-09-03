#ifndef __NODE__H
#define __NODE__H

#include <stdio.h>
#include <iostream>
#include <exception>

class Node;
class doubleNode;
class intNode;
class addNode;
class subNode;
class divNode;
class multNode;
#define DEBUG_BUILD
#include "visitors.h"
#include "debug.h"


class divByZeroException : public std::exception {
    virtual const char* what() const throw(){
      return "Divide by Zero.";
    }
};


class syntaxErrorException : public std::exception {
    virtual const char* what() const throw(){
      return "syntax error.";
    }
};

class Node{
  public:
    Node();
    virtual ~Node();
    virtual void setLeft(Node *_l);
    virtual void setRight(Node *_r);
    virtual Node* getLeft() const;
    virtual Node* getRight() const;
    virtual void identify() const;
    virtual void accept(Visitor* _v) const = 0;

    virtual Node* clone() const = 0;

    virtual Node* operator+( const Node& r) const;
    virtual Node* operator+( const intNode& r) const;
    virtual Node* operator+( const doubleNode& r) const;

    virtual Node* operator-( const Node& r ) const  ;
    virtual Node* operator-( const intNode& r ) const  ;
    virtual Node* operator-( const doubleNode& r ) const ;

    virtual Node* operator/( const Node& r ) const  ;
    virtual Node* operator/( const intNode& r ) const  ;
    virtual Node* operator/( const doubleNode& r ) const ;

    virtual Node* operator*( const Node& r ) const  ;
    virtual Node* operator*( const intNode& r ) const  ;
    virtual Node* operator*( const doubleNode& r ) const ;

    virtual bool operator==( const Node& r) const;
    virtual bool operator==( const intNode& r) const;
    virtual bool operator==( const doubleNode& r) const;
  private:
    Node *l,*r;
};

template <class T>
class elementaryNode : public Node{
  public:
    virtual T getValue() const {return value;};
    virtual void setValue(T _value) {value = _value;};
    elementaryNode(T _v) {setValue(_v);};
  private:
    T value;
};

class intNode : public elementaryNode<int> {
  public:
    intNode(int value);
    virtual void accept(Visitor* _v) const;
     virtual void identify() const;

    virtual Node* clone() const;
     virtual Node* operator+( const Node& r) const;
     virtual Node* operator+( const doubleNode& r) const;
     virtual Node* operator+( const intNode& r) const;


     virtual Node* operator-( const Node& r ) const  ;
     virtual Node* operator-( const doubleNode& r ) const  ;
     virtual Node* operator-( const intNode& r ) const  ;

    virtual Node* operator/( const Node& r ) const  ;
    virtual Node* operator/( const intNode& r ) const  ;
    virtual Node* operator/( const doubleNode& r ) const ;

    virtual Node* operator*( const Node& r ) const  ;
    virtual Node* operator*( const intNode& r ) const  ;
    virtual Node* operator*( const doubleNode& r ) const ;

    virtual bool operator==(   const Node& r) const;
    virtual bool operator==(   const intNode& r) const;
    virtual bool operator==(   const doubleNode& r) const;
};


class doubleNode : public elementaryNode<double> {
  public:
    doubleNode(double value);
    virtual void accept(Visitor* _v) const;
    virtual void identify() const;
    virtual Node* clone() const;
    virtual Node* operator+( const Node& r) const;
    virtual Node* operator+( const intNode& r) const;
    virtual Node* operator+( const doubleNode& r) const;

    virtual Node* operator-( const Node& r ) const  ;
    virtual Node* operator-( const doubleNode& r ) const  ;
    virtual Node* operator-( const intNode& r ) const  ;

    virtual Node* operator/( const Node& r ) const  ;
    virtual Node* operator/( const intNode& r ) const  ;
    virtual Node* operator/( const doubleNode& r ) const ;

    virtual Node* operator*( const Node& r ) const  ;
    virtual Node* operator*( const intNode& r ) const  ;
    virtual Node* operator*( const doubleNode& r ) const ;

    virtual bool operator==(   const Node& r) const ;
    virtual bool operator==(   const intNode& r) const ;
    virtual bool operator==(   const doubleNode& r) const ;
};


class addNode : public Node {
  public:
    addNode(Node *_l, Node *_r);
    virtual void identify() const;
    virtual Node* clone() const;
    virtual void accept(Visitor* _v) const;
};

class subNode : public Node {
  public:
    subNode(Node *_l, Node *_r);
    virtual Node* clone() const;
    virtual void accept(Visitor* _v) const;
};

class divNode : public Node {
  public:
    divNode(Node *_l, Node *_r);
    virtual Node* clone() const;
    virtual void accept(Visitor* _v) const;
};

class multNode : public Node {
  public:
    multNode(Node *_l, Node *_r);
    virtual Node* clone() const;
    virtual void accept(Visitor* _v) const;
};

#endif
