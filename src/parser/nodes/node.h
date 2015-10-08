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

class intArrayNode;
class doubleArrayNode;

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

    friend bool operator==( const terminalNode& l, const terminalNode& r);

    terminalNode* negate() const {return _negate();};
    terminalNode* bang() const {return _bang();};

  private:

    virtual terminalNode* _add( const terminalNode& r) const {throw syntaxError();};
    virtual terminalNode* _add( const intNode& r) const {throw syntaxError();};
    virtual terminalNode* _add( const doubleNode& r) const {throw syntaxError();};

    virtual terminalNode* _sub( const terminalNode& r) const {throw syntaxError();};
    virtual terminalNode* _sub( const intNode& r) const {throw syntaxError();};
    virtual terminalNode* _sub( const doubleNode& r) const {throw syntaxError();};

    virtual terminalNode* _div( const terminalNode& r) const {throw syntaxError();};
    virtual terminalNode* _div( const intNode& r) const {throw syntaxError();};
    virtual terminalNode* _div( const doubleNode& r) const {throw syntaxError();};

    virtual terminalNode* _mult( const terminalNode& r) const {throw syntaxError();};
    virtual terminalNode* _mult( const intNode& r) const {throw syntaxError();};
    virtual terminalNode* _mult( const doubleNode& r) const {throw syntaxError();};

    virtual terminalNode* _negate() const {throw syntaxError();};
    virtual terminalNode* _bang() const {throw syntaxError();};


    virtual bool eq( const terminalNode& r) const {throw syntaxError();};
    virtual bool eq( const intNode& r) const {throw syntaxError();};
    virtual bool eq( const doubleNode& r) const {throw syntaxError();};

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
    virtual terminalNode* _add( const terminalNode& r) const;
    virtual terminalNode* _add( const intNode& r) const;
    virtual terminalNode* _add( const doubleNode& r) const;

    virtual terminalNode* _sub( const terminalNode& r) const;
    virtual terminalNode* _sub( const intNode& r) const;
    virtual terminalNode* _sub( const doubleNode& r) const;

    virtual terminalNode* _div( const terminalNode& r) const;
    virtual terminalNode* _div( const intNode& r) const;
    virtual terminalNode* _div( const doubleNode& r) const;

    virtual terminalNode* _mult( const terminalNode& r) const;
    virtual terminalNode* _mult( const intNode& r) const;
    virtual terminalNode* _mult( const doubleNode& r) const;

    virtual terminalNode* _negate() const;
    virtual terminalNode* _bang() const;

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
    virtual terminalNode* _add( const terminalNode& r) const;
    virtual terminalNode* _add( const intNode& r) const;
    virtual terminalNode* _add( const doubleNode& r) const;

    virtual terminalNode* _sub( const terminalNode& r) const;
    virtual terminalNode* _sub( const intNode& r) const;
    virtual terminalNode* _sub( const doubleNode& r) const;

    virtual terminalNode* _div( const terminalNode& r) const;
    virtual terminalNode* _div( const intNode& r) const;
    virtual terminalNode* _div( const doubleNode& r) const;

    virtual terminalNode* _mult( const terminalNode& r) const;
    virtual terminalNode* _mult( const intNode& r) const;
    virtual terminalNode* _mult( const doubleNode& r) const;

    virtual terminalNode* _negate() const;
    virtual terminalNode* _bang() const;

    virtual bool eq( const terminalNode& r) const;
    virtual bool eq( const intNode& r) const;
    virtual bool eq( const doubleNode& r) const;
};

class intArrayNode : public elementaryNode<int*> {
};


class doubleArrayNode : public elementaryNode<double*> {
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
