#include <stdio.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "parser/nodes/node.h"
#include "gtest/gtest.h"


inline void check(const char *str,double _value){
  const Node *root=NULL, *result=NULL;
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

  EXPECT_EQ((*result),(*value));
	delete root;
	delete result;
	delete value;
}


TEST(LPL,Arithmetic){
  check("1+2",3);
  check("1+2*3",7);
  check("1+2*3.0",7);
  check("(1+2)*(3+4)",21);
  check("(1*2)+(3*4)",14);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

