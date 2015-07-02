#ifndef NODE_H
#define NODE_H


typedef enum { tint, tdouble, tchar, top } types;

typedef enum { plus } ops;

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

node* newNode(const char *str,types type, node* l, node* r);
node* evalNode(node* root);

#endif
