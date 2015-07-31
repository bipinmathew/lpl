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
    virtual Node* clone(){return this;};
    virtual void identify(){std::cout<<"I am a generic node."<<std::endl;};
    virtual void accept(Visitor* _v){std::cout<<"Visiting generic node."<<std::endl; _v->visit(this);};
    virtual Node& operator+(const Node& r){
      Node* v = new Node();
      printf(">This is an error 0.<\n");
      return *v;
    }
    virtual Node& operator+(const doubleNode& r){
      Node* v = new Node();
      printf(">This is an error 1.<\n");
      return *v;
    }
    virtual Node& operator+(const intNode& r){
      Node* v = new Node();
      printf(">This is an error 2.<\n");
      return *v;
    }
  private:
    Node *l,*r;
};

template <class T>
class elementaryNode : public Node {
  public:
    virtual T getValue() {return value;};
    virtual void setValue(T _value) {value = _value;};
    virtual elementaryNode* clone(){return this;};
    virtual void identify(){std::cout<<"I am a elementary node."<<std::endl;};
  private:
    T value;
};


class doubleNode : public elementaryNode <double> {
  public:
    virtual doubleNode* clone(){return this;};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a double node."<<std::endl;};
    virtual doubleNode& operator+(const doubleNode& r){
      doubleNode* v = new doubleNode();
      printf("promoted to double!\n");
      return *v;
    }
};


class intNode : public elementaryNode <int>{
  public:
    virtual intNode* clone(){return this;};
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a int node."<<std::endl;};
    virtual doubleNode& operator+(const Node& r){
      doubleNode* v = new doubleNode();
      printf("promoted to double2!\n");
      return *v;
    }
};


class addNode : public Node {
  public:
    virtual void accept(Visitor* _v){_v->visit(this);};
    virtual void identify(){std::cout<<"I am a add node."<<std::endl;};
};


class evalVisitor : public Visitor {
  public:
    void visit(doubleNode *_elm);
    void visit(intNode *_elm);
    void visit(addNode *_elm);
    void visit(Node *_elm);
  private:
    std::stack <Node*> S;

};

void evalVisitor::visit(doubleNode *_elm){std::cout<<"Visited a double."<<std::endl; S.push(_elm);};
void evalVisitor::visit(intNode *_elm){std::cout<<"Visited a int."<<std::endl; S.push(_elm);};
void evalVisitor::visit(addNode *_elm){
  printf("Visit addNode.\n");
  Node& l = *S.top();
  S.pop();

  Node& r = *S.top();
  S.pop();


  S.push(&(l+r));

  l.identify();
  r.identify();
  
  //std::cout<<"Visited a add: "<< l+r << std::endl; 
  // S.top()->clone();
};
void evalVisitor::visit(Node *_elm){std::cout<<"Visited a generic."<<std::endl;};



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


  //a.getLeft()->accept(v);
  //a.getRight()->accept(v);
  //a.accept(v);

}
