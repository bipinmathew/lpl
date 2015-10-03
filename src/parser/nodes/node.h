#ifndef __NODE__H
#define __NODE__H

#include <stdio.h>
#include <iostream>
#include <vector>

class Node;
class terminalNode;
class doubleNode;
class intNode;
class addNode;
class subNode;
class divNode;
class multNode;
class negNode;

class bangNode;

#include "node_errors.h"
#include "visitors.h"
#include "debug.h"


class Node{
  public:
    virtual ~Node();
    void acceptVisitor(Visitor* _v) const { return accept(_v); };

    void print() const { return _print(); };
    virtual Node* clone() const = 0;

    const std::vector<Node*>& getChildren() const {return children;};
    void addChild(Node *_c);

    friend std::ostream& operator<< (std::ostream& os, const Node& rhs){ return rhs.print(os); }

  private:
    std::vector<Node*> children;
    virtual void accept(Visitor* _v) const = 0;
    virtual void _print () const;
    virtual std::ostream& print (std::ostream& rhs) const;
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

    friend terminalNode* negate( const terminalNode& l);
    friend terminalNode* bang( const terminalNode& l);

    friend bool operator==( const terminalNode& l, const terminalNode& r);

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

    virtual terminalNode* neg() const = 0;

    virtual bool eq( const terminalNode& r) const = 0;
    virtual bool eq( const intNode& r) const = 0;
    virtual bool eq( const doubleNode& r) const = 0;

};


template <class T>
class elementaryNode : public terminalNode{
  public:
    T getValue() const {return value;};
    void setValue(T _value) {value = _value;};
    elementaryNode(T _v) : value(_v) {};
  private:
    T value;
};

class intNode : public elementaryNode<int> {
  public:
    intNode(int value);
    virtual terminalNode* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
    virtual std::ostream& print(std::ostream& os) const;
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

    virtual terminalNode* neg() const;

    virtual bool eq( const terminalNode& r) const;
    virtual bool eq( const intNode& r) const;
    virtual bool eq( const doubleNode& r) const;
};

std::ostream &operator<<(std::ostream &os, intNode const *rhs);

class doubleNode : public elementaryNode<double> {
  public:
    doubleNode(double value);
    virtual terminalNode* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
    std::ostream& print(std::ostream& os) const;
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

    virtual terminalNode* neg() const;

    virtual bool eq( const terminalNode& r) const;
    virtual bool eq( const intNode& r) const;
    virtual bool eq( const doubleNode& r) const;
};


std::ostream &operator<<(std::ostream &os, doubleNode const *rhs);


class addNode : public Node {
  public:
    addNode(Node *_l, Node *_r);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};

class subNode : public Node {
  public:
    subNode(Node *_l, Node *_r);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};

class divNode : public Node {
  public:
    divNode(Node *_l, Node *_r);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};


class multNode : public Node {
  public:
    multNode(Node *_l, Node *_r);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};



class negNode : public Node {
  public:
    negNode(Node *_l);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};


class bangNode : public Node {
  public:
    bangNode(Node *_l);
    Node* clone() const;
  private:
    virtual void accept(Visitor* _v) const;
    virtual void _print() const;
};




#endif
