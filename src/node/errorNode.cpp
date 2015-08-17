#include "node.h"

errorNode::errorNode( std::string s ) : elementaryNode<std::string>(s){}
Node* errorNode::clone(){return new errorNode(*this);}
void errorNode::accept( Visitor *_v){_v->visit(this);}
