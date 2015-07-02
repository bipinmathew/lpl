#ifndef NODE_H
#define NODE_H

#define TINT 0
#define TDOUBLE 1
#define TCHAR 2
#define TPLUS 3

typedef union d {
  int i;
  double d;
  char c;
} uvalue;

typedef struct node {
  int type;
  uvalue value;
  struct node *l,*r;
} node;

node* newNode(const char *str,int type,const node* l, const node* r);

#endif
