#include "node.h"

errorNode::errorNode( std::string s ) : elementaryNode<std::string>(s){}
void errorNode::accept( Visitor *_v){_v->visit(this);}
