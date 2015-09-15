#include <stdio.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "parser/nodes/node.h"

bool check(const char *str,double _value){
  const Node *root=NULL;
  const terminalNode *result=NULL;
	bool r=0;
  int retval;
  doubleNode *value;

  printf("Trying: %s\n",str);

	try{
    value = new doubleNode(_value);
    root=parse(str);
		result = eval(root);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
    if (root!=NULL)  delete root;
		delete value;
    throw;
	}

  r = !((*result)==(*value));
	delete root;
	delete result;
	delete value;
	return r;
}

int main() {
  FILE *fp;
  char commandLine[1024];
  Node *result;

  fp = fopen("errors.log","w");
  ParseTrace(fp,"err: ");

  while (scanf("%s",commandLine)) {
    try{
          std::cout << *eval(parse(commandLine)) << std::endl;
    }
    catch(std::exception &e){
      std::cerr << e.what() << std::endl;
    }

  }
  fclose(fp);
  return 0;
}
