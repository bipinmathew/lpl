#include "node.h"


Node::Node(){l=NULL;r=NULL;};
void Node::setLeft(Node *_l){l = _l;};
void Node::setRight(Node *_r){r = _r;};
Node* Node::getLeft(){return l;};
Node* Node::getRight(){return r;};
void Node::identify(){std::cout<<"I am a generic node."<<std::endl;};
Node* Node::operator+(   Node& r)  {
      return new errorNode("node+node error.");
    }
Node* Node::operator+(  doubleNode& r){
    return r+(*this);
}
 Node* Node::operator+(   intNode& r)  {
    return r+(*this);
}


Node* doubleNode::operator+(  Node& r){
      return r+(*this);
}
Node* doubleNode::operator+(  doubleNode& r){
  dbg("double class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* doubleNode::operator+(  intNode& r){
  dbg("double class doing int addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}


Node* intNode::operator+(   Node& r){
      return r+(*this);
}
Node* intNode::operator+(   doubleNode& r){
  dbg("int class doing double addition"<<std::endl);
  return new doubleNode(getValue()+r.getValue());
}
Node* intNode::operator+(   intNode& r){
  dbg("int class doing int addition"<<std::endl);
  return new intNode(getValue()+r.getValue());
}

intNode::intNode(){};
intNode::intNode(int value) : elementaryNode<int> (value){};
void intNode::accept(Visitor* _v){_v->visit(this);};
void intNode::identify(){std::cout<<"I am a int node."<<std::endl;};
Node* intNode::operator+(   Node& r) ;
Node* intNode::operator+(   doubleNode& r) ;
Node* intNode::operator+(   intNode& r) ;



doubleNode::doubleNode(){};
doubleNode::doubleNode(double value) : elementaryNode<double> (value){};
void doubleNode::accept(Visitor* _v){_v->visit(this);};
void doubleNode::identify(){std::cout<<"I am a double node."<<std::endl;};
Node* doubleNode::operator+(  Node& r);
Node* doubleNode::operator+(  intNode& r);
Node* doubleNode::operator+(  doubleNode& r);


errorNode::errorNode( std::string s ) : elementaryNode<std::string>(s){};
void errorNode::accept( Visitor *_v){_v->visit(this);};


void addNode::accept(Visitor* _v){_v->visit(this);};

void evalVisitor::visit(Node *_elm){dbg("Visited a generic."<<std::endl);};
void evalVisitor::visit(doubleNode *_elm){dbg("Visited a double."<<std::endl); S.push(_elm);};
void evalVisitor::visit(intNode *_elm){dbg("Visited a int."<<std::endl); S.push(_elm);};
void evalVisitor::visit(addNode *_elm){
  dbg("Visit addNode." << std::endl);
  Node *l, *r;
  l = S.top();
  l->identify();
  S.pop();

  r = S.top();
  r->identify();
  S.pop();

  S.push((*l)+(*r));
};


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
