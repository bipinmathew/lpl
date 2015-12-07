#include <stdio.h>
#include <stdlib.h>
extern "C" {
  #include "parser.h"
};

bool check(const char *str,double _value){
    node n,*result;
    int val;
    n.type = tdouble;
    n.value.d = _value;

    printf("Trying %s \n",str);

    result=parse(str);
    val=isEqual(&n,result);
    freeNode(result);
    return val;
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
  check("1.0/0",1);
}

