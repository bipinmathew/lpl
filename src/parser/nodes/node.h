#ifndef __NODE__H
#define __NODE__H

#include <stdio.h>
#include <iostream>
#include <exception>

class Node;
class terminalNode;
class doubleNode;
class intNode;
class addNode;
class subNode;
class divNode;
class multNode;
#include "visitors.h"
#include "debug.h"


class divByZeroError : public std::exception {
    virtual const char* what() const throw(){
      return "Divide by Zero.";
    }
};


class syntaxError : public std::exception {
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


    friend std::ostream& operator<< (std::ostream& os, const Node& rhs){ return rhs.print(os); }
  private:
    virtual std::ostream& print (std::ostream& rhs) const;
    Node *l,*r;
};

std::ostream &operator<<(std::ostream &os, Node const *rhs);


class terminalNode : public Node {
  public:
    friend class intNode;
    friend class doubleNode;

    friend terminalNode* operator+( const terminalNode& l, const terminalNode& r );
    friend terminalNode* operator-( const terminalNode& l, const terminalNode& r );
    friend terminalNode* operator/( const terminalNode& l, const terminalNode& r );
    friend terminalNode* operator*( const terminalNode& l, const terminalNode& r );
    bool operator==( const terminalNode& r) const;

  private:
    virtual terminalNode* add( const terminalNode& r) const = 0;
    virtual terminalNode* add( const intNode& r) const = 0;
    virtual terminalNode* add( const doubleNode& r) const = 0;

    virtual terminalNode* sub( const terminalNode& r) const = 0;
    virtual terminalNode* sub( const intNode& r) const = 0;
    virtual terminalNode* sub( const doubleNode& r) const = 0;

    virtual terminalNode* div( const terminalNode& r) const = 0;
    virtual terminalNode* div( const intNode& r) const = 0;
    virtual terminalNode* div( const doubleNode& r) const = 0;

    virtual terminalNode* mult( const terminalNode& r) const = 0;
    virtual terminalNode* mult( const intNode& r) const = 0;
    virtual terminalNode* mult( const doubleNode& r) const = 0;

    virtual bool eq( const terminalNode& r) const = 0;
    virtual bool eq( const intNode& r) const = 0;
    virtual bool eq( const doubleNode& r) const = 0;

};


template <class T>
class elementaryNode : public terminalNode{
  public:
    virtual T getValue() const {return value;};
    virtual void setValue(T _value) {value = _value;};
    elementaryNode(T _v) {setValue(_v);};
  private:
    T value;
};

class intNode : public elementaryNode<int> {
  public:
    friend class Node;
    intNode(int value);
    virtual void accept(Visitor* _v) const;
    virtual void identify() const;

    virtual std::ostream& print(std::ostream& os) const;


    virtual terminalNode* clone() const;

  private:
    virtual terminalNode* add( const terminalNode& r) const;
    virtual terminalNode* add( const intNode& r) const;
    virtual terminalNode* add( const doubleNode& r) const;

    virtual terminalNode* sub( const terminalNode& r) const;
    virtual terminalNode* sub( const intNode& r) const;
    virtual terminalNode* sub( const doubleNode& r) const;

    virtual terminalNode* div( const terminalNode& r) const;
    virtual terminalNode* div( const intNode& r) const;
    virtual terminalNode* div( const doubleNode& r) const;

    virtual terminalNode* mult( const terminalNode& r) const;
    virtual terminalNode* mult( const intNode& r) const;
    virtual terminalNode* mult( const doubleNode& r) const;

    virtual bool eq( const terminalNode& r) const;
    virtual bool eq( const intNode& r) const;
    virtual bool eq( const doubleNode& r) const;
};

std::ostream &operator<<(std::ostream &os, intNode const *rhs);

class doubleNode : public elementaryNode<double> {
  public:
    friend class Node;
    doubleNode(double value);
    virtual void accept(Visitor* _v) const;
    virtual void identify() const;


    std::ostream& print(std::ostream& os) const;

    virtual terminalNode* clone() const;

  private:
    virtual terminalNode* add( const terminalNode& r) const;
    virtual terminalNode* add( const intNode& r) const;
    virtual terminalNode* add( const doubleNode& r) const;

    virtual terminalNode* sub( const terminalNode& r) const;
    virtual terminalNode* sub( const intNode& r) const;
    virtual terminalNode* sub( const doubleNode& r) const;

    virtual terminalNode* div( const terminalNode& r) const;
    virtual terminalNode* div( const intNode& r) const;
    virtual terminalNode* div( const doubleNode& r) const;

    virtual terminalNode* mult( const terminalNode& r) const;
    virtual terminalNode* mult( const intNode& r) const;
    virtual terminalNode* mult( const doubleNode& r) const;

    virtual bool eq( const terminalNode& r) const;
    virtual bool eq( const intNode& r) const;
    virtual bool eq( const doubleNode& r) const;
};


std::ostream &operator<<(std::ostream &os, doubleNode const *rhs);


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
