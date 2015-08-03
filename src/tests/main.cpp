#include <stdio.h>
#include <iostream>
#include <stack>
#include <memory>

class Node;
class doubleNode;
class intNode;
class addNode;

class Visitor {
  public:
    virtual void visit(doubleNode *_elm){};
    virtual void visit(intNode *_elm){};
    virtual void visit(addNode *_elm){};
    virtual void visit(Node *_elm){};
};

class Node{
  public:
    Node(){l=NULL;r=NULL;};
    virtual void setLeft(Node *_l){l = _l;};
    virtual void setRight(Node *_r){r = _r;};
    virtual Node* getLeft(){return l;};
    virtual Node* getRight(){return r;};
    virtual void identify(){std::cout<<"I am a generic node."<<std::endl;};
    virtual Node* clone(){return new Node(*this);};
    virtual void accept(Visitor* _v){std::cout<<"Visiting generic node."<<std::endl; _v->visit(this);};

    virtual Node* _add(Node *r);
    virtual Node* _add(doubleNode *r);
    virtual Node* _add(intNode *r);
  private:
    Node *l,*r;
};

template <class T>
class elementaryNode : public Node {
  public:
    virtual T getValue() {return value;};
    virtual void setValue(T _value) {value = _value;};
  private:
    T value;
};


class intNode : public elementaryNode <int>{
  public:
    intNode(){};
    intNode(int value){setValue(value);};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a int node."<<std::endl;};
    virtual Node* _add(Node *r);
    virtual intNode* _add(doubleNode *r);
    virtual intNode* _add(intNode *r);
    virtual intNode* clone(){return new intNode(*this);};
};


class doubleNode : public elementaryNode <double> {
  public:
    doubleNode(){};
    doubleNode(double value){setValue(value);};
    doubleNode(doubleNode* l){setValue(l->getValue());};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual doubleNode* _add(doubleNode *r);
    virtual void identify(){std::cout<<"I am a double node."<<std::endl;};
    virtual Node* _add(Node *r);
    virtual doubleNode* _add(intNode *r);
    virtual doubleNode* clone(){return new doubleNode(*this);};

};




class addNode : public Node {
  public:
    virtual void accept(Visitor* _v){_v->visit(this);};
};


class evalVisitor : public Visitor {
  public:
    void visit(doubleNode *_elm);
    void visit(intNode *_elm);
    void visit(addNode *_elm);
    void visit(Node *_elm);
    double visit(double* _elm);
    int visit(int* _elm);
  private:
    std::stack <Node*> S;

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

  S.push(l->_add(r));
};

class errorNode : public elementaryNode<std::string> {
  public:
    errorNode(const char *s){setValue(s);};

};


Node* Node::_add(Node *r){
      return new errorNode("node+node error.");
    }
Node* Node::_add(doubleNode *r){
    return r->_add(this);
}
Node* Node::_add(intNode *r){
    return r->_add(this);
}


Node* doubleNode::_add(Node *r){
      return r->_add(this);
}
doubleNode* doubleNode::_add(doubleNode *r){
  std::cout<<"double class doing double addition"<<std::endl;
  return new doubleNode(getValue()+r->getValue());
}
doubleNode* doubleNode::_add(intNode *r){
  std::cout<<"double class doing int addition"<<std::endl;
  return new doubleNode(getValue()+r->getValue());
}


Node* intNode::_add(Node *r){
      return r->_add(this);
}
intNode* intNode::_add(doubleNode *r){
  std::cout<<"int class doing double addition"<<std::endl;
  return new intNode(getValue()+r->getValue());
}
intNode* intNode::_add(intNode *r){
  std::cout<<"int class doing int addition"<<std::endl;
  return new intNode(getValue()+r->getValue());
}


int main(){
  doubleNode d;
  intNode i;
  addNode a;
  evalVisitor v;
  Node *t;

  d.setValue(3.4);
  i.setValue(8);
  a.setLeft(&d);
  a.setRight(&i);

  i.accept(&v);
  d.accept(&v);
  a.accept(&v);
}
