#include <stdio.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "parser/nodes/node.h"
#include "parser/nodes/visitors.h"

int main() {
  FILE *fp;
  char commandLine[1024];
  evalVisitor *v = new evalVisitor();
  Node *result;


  while (scanf("%s",commandLine)) {
    try{
          v->eval(parse(commandLine));
          std::cout << *v->getTop() << std::endl;
    }
    catch(std::exception &e){
      std::cerr << e.what() << std::endl;
    }
    v->cleanup();
  }
  return 0;
}
