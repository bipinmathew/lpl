#ifndef NODE_H
#define NODE_H


typedef enum { tnull, tint, tdouble, tchar, top, terror, tarray  } types;

typedef enum { add, minus, mult, odiv } ops;

typedef union {
  int i;
  double d;
  char c;
  char *s;
  ops op;
} uvalue;


typedef struct _node {
  types type;
  uvalue value;
  struct _node* l;
  struct _node* r;
} node;

int initNode(node **p);
node* newNode(const char *str,types type, node* const l, node* const r);
node* evalNode(const node* root);
void printNode(node* n);

#endif
