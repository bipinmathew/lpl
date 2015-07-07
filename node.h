#ifndef NODE_H
#define NODE_H


typedef enum { tnull, tint, tdouble, tchar, top, terror  } types;

typedef enum { plus, minus, mult } ops;

typedef union {
  int i;
  double d;
  char c;
  ops op;
} uvalue;


typedef struct Node{
  types type;
  uvalue value;
  struct Node* l;
  struct Node* r;
} node;

int initNode(node **p);
node* newNode(const char *str,types type, node *l, node *r);
node* evalNode(const node* root);
void printNode(node* n);

#endif
