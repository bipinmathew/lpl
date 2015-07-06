#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      n->value.d = atof(str);
      printf("creating double node.\n");
    break;
    default:
      printf("Bad!");
  }

  n->l = l;
  n->r = r;
  return n;
};

int freeNode(node *n){
  if(n->l != NULL)
    freeNode(n->l);
  if(n->r != NULL)
    freeNode(n->r);
  free(n); 
}

void print(node* n){
  switch(n->type){
    case top:
      switch(n->value.op){
        case plus:
          print(n->l);
          printf("+");
          print(n->r);
        break;
        default:
          printf("Error evaluating expression.");
      }
    break;
    case tint:
        printf("%d",n->value.i);
    break;
    case tdouble:
        printf("%f",n->value.d);
    break;
    default:
      printf("Bad!");
  }
}

node* _plus(const node* l, const node* r){
  node *out;
  out = (node*) malloc(sizeof(node));
  switch(l->type){
    case tint:
      switch(r->type){
        case tint:
          out->type = tint;
          out->value.i = l->value.i+r->value.i; 
        break;
        case tdouble:
          out->type = tdouble;
          out->value.d = l->value.i+r->value.d; 
        break;
        default:
          printf("Syntax error.");
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          out->type = tdouble;
          out->value.d = l->value.d+r->value.i;
          
        break;
        case tdouble:
          out->type = tdouble;
          out->value.d = l->value.d+r->value.d;
        break;
        default:
          printf("Syntax error.");
        break;

      }
    break;
  }
  return(out);
}

node* evalNode(node* n){
  node *out;
  switch(n->type){
    case top:
      switch(n->value.op){
        case plus:
          out = _plus(evalNode(n->l),evalNode(n->r));
        break;
        default:
          printf("Error evaluating expression.");
      }
    break;
    case tint:
      out = n;
      // memcpy(out,n,sizeof(node));
    break;
    case tdouble:
      out = n;
      // memcpy(out,n,sizeof(node));
    break;
    default:
      printf("Bad!");
  }

  return out;
  
};
