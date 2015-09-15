#include <stdio.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "parser/nodes/node.h"
#include "gtest/gtest.h"


bool check(const char *str,double _value){
  const Node *root=NULL;
  const terminalNode *result=NULL;
	bool r=0;
  int retval;
  doubleNode *value;

  //printf("Trying: %s\n",str);

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

  r= ((*result)==(*value));
	delete root;
	delete result;
	delete value;
  return r;
}


TEST(LPL,Arithmetic){
  EXPECT_TRUE(check("1+2",3));
  EXPECT_TRUE(check("1+2*3",7));
  EXPECT_TRUE(check("1+2*3.0",7));
  EXPECT_TRUE(check("(1+2)*(3+4)",21));
  EXPECT_TRUE(check("(1*2)+(3*4)",14));


  EXPECT_TRUE(check("1+2",3));
  EXPECT_TRUE(check("1+2+3",6));
  EXPECT_TRUE(check("3+4.0",7));
  EXPECT_TRUE(check("5.0+6",11));

  EXPECT_TRUE(check("1-2",-1));
  EXPECT_TRUE(check("1-2-3",-4));
  EXPECT_TRUE(check("3-4.0",-1));
  EXPECT_TRUE(check("5.0-6",-1));

  EXPECT_TRUE(check("1*2",2));
  EXPECT_TRUE(check("1*2*3",6));
  EXPECT_TRUE(check("3*4.0",12));
  EXPECT_TRUE(check("5.0*6",30));


  EXPECT_TRUE(check("1/2",0.5));
  EXPECT_TRUE(check("3/4.0",0.75));
  EXPECT_TRUE(check("5.0/6",5.0/6));
}


TEST(LPL,Exceptions){
  EXPECT_THROW(check("9+(1+2)/0",10),divByZeroError);
  EXPECT_THROW(check("+++",10),syntaxError);
  EXPECT_THROW(check("3+++3",6),syntaxError);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

