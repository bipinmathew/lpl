#include <stdio.h>
#include <iostream>
#include <stack>
#include <memory>

class Node;
class doubleNode;
class intNode;
class addNode;
class errorNode;

class Visitor {
  public:
    virtual void visit(Node *_elm)=0;
    virtual void visit(intNode *_elm)=0;
    virtual void visit(doubleNode *_elm)=0;
    virtual void visit(addNode *_elm)=0;
};

class evalVisitor : public Visitor {
  public:
    void visit(Node *_elm);
    void visit(intNode *_elm);
    void visit(doubleNode *_elm);
    void visit(addNode *_elm);
  private:
    std::stack <Node*> S;

};

class Node{
  public:
    Node(){l=NULL;r=NULL;};
    virtual void setLeft(Node *_l){l = _l;};
    virtual void setRight(Node *_r){r = _r;};
    virtual Node* getLeft(){return l;};
    virtual Node* getRight(){return r;};
    virtual void identify(){std::cout<<"I am a generic node."<<std::endl;};
    virtual void accept(Visitor* _v) = 0;

    virtual Node* operator+(  Node& r);
    virtual Node* operator+(  intNode& r);
    virtual Node* operator+(  doubleNode& r);
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
    intNode(){};
    intNode(int value) : elementaryNode<int> (value){};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a int node."<<std::endl;};
    virtual Node* operator+(  Node& r);
    virtual Node* operator+(  doubleNode& r);
    virtual Node* operator+(  intNode& r);
};


class doubleNode : public elementaryNode<double> {
  public:
    doubleNode(){};
    doubleNode(double value) : elementaryNode<double> (value){};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a double node."<<std::endl;};
    virtual Node* operator+(  Node& r);
    virtual Node* operator+(  intNode& r);
    virtual Node* operator+(  doubleNode& r);
};


class errorNode : public elementaryNode<std::string>{
  public:
    errorNode( char *s){setValue(s);};
    virtual void accept( Visitor *_v){_v->visit(this);};
};


class addNode : public Node {
  public:
    virtual void accept(Visitor* _v){_v->visit(this);};
};




void evalVisitor::visit(Node *_elm){std::cout<<"Visited a generic."<<std::endl;};
void evalVisitor::visit(doubleNode *_elm){std::cout<<"Visited a double."<<std::endl; S.push(_elm);};
void evalVisitor::visit(intNode *_elm){std::cout<<"Visited a int."<<std::endl; S.push(_elm);};
void evalVisitor::visit(addNode *_elm){
  printf("Visit addNode.\n");
  Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)+(*r));

  l = S.top();
  l->identify();
  S.pop();
};



Node* Node::operator+(  Node& r){
      return new errorNode("node+node error.");
    }
Node* Node::operator+(  doubleNode& r){
    return r+(*this);
}
Node* Node::operator+(  intNode& r){
    return r+(*this);
}


Node* doubleNode::operator+(  Node& r){
      return r+(*this);
}
Node* doubleNode::operator+(  doubleNode& r){
  std::cout<<"double class doing double addition"<<std::endl;
  return new doubleNode(getValue()+r.getValue());
}
Node* doubleNode::operator+(  intNode& r){
  std::cout<<"double class doing int addition"<<std::endl;
  return new doubleNode(getValue()+r.getValue());
}


Node* intNode::operator+(  Node& r){
      return r+(*this);
}
Node* intNode::operator+(  doubleNode& r){
  std::cout<<"int class doing double addition"<<std::endl;
  return new doubleNode(getValue()+r.getValue());
}
Node* intNode::operator+(  intNode& r){
  std::cout<<"int class doing int addition"<<std::endl;
  return new intNode(getValue()+r.getValue());
}


int main(){
  doubleNode d;
  intNode i;
  addNode a;
  evalVisitor v;
  Node *t;

  d.setValue(3.8);
  i.setValue(8);
  a.setLeft(&d);
  a.setRight(&i);

  i.accept(&v);
  d.accept(&v);
  a.accept(&v);
}
