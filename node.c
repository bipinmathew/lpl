#include "node.h"
#include <stdio.h>
#include <stdlib.h>

node* newNode(const char *str,types type, node* l, node* r){
  node *n;
  n = (node*)malloc(sizeof(node));

  n->type = type;
  switch(n->type){
    case top:
      if(0==strcmp("+",str)){
        n->value.op = plus;
        printf("  created plus node.\n"); 
      }
      else if(0==strcmp("-",str)){
      }
      else if(0==strcmp("*",str)){
      }
    break;
    case tint:
      printf("creating int node.\n");
      n->value.i = atoi(str);
    break;
    case tdouble:
      printf("creating double node.\n");
    break;
    default:
      printf("Bad!");
  }

  n->l = l;
  n->r = r;
  return n;
};

node* evalNode(node* root){
  
};
