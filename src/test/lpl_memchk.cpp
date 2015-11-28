#include <stdio.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "parser/nodes/node.h"
#include "parser/nodes/visitors.h"


bool check(const char *str,double _value){
  const Node *root=NULL;
  const terminalNode *result=NULL;
  evalVisitor *v = new evalVisitor();
	bool r=0;
  int retval;
  doubleNode *value;

  printf("Trying: %s\n",str);

	try{
    value = new doubleNode(_value);
    root=parse(str);
		v->eval(root);
    result = v->getTop();
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
    if (root!=NULL)  delete root;
		delete value;
    delete v;
    return false;
	}

  r= ((*result)==(*value));
	delete root;
	delete value;
  delete v;
  return r;
}

int main(int argc, char **argv) {
  check("1+2",3);
  check("1+2*3",7);
  check("1+2*3.0",7);
  check("(1+2)*(3+4)",21);
  check("(1*2)+(3*4)",14);


  check("1+2",3);
  check("1+2+3",6);
  check("3+4.0",7);
  check("5.0+6",11);

  check("1-2",-1);
  check("1-2-3",-4);
  check("3-4.0",-1);
  check("5.0-6",-1);

  check("1*2",2);
  check("1*2*3",6);
  check("3*4.0",12);
  check("5.0*6",30);


  check("1/2",0.5);
  check("3/4.0",0.75);
  check("5.0/6",5.0/6);

  check("5.0/0",1.0);
  check("1/0",1);
}

