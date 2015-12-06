#ifndef NODE_H
#define NODE_H


typedef enum { tnull, tboolean, tint, tdouble, tchar, terror, tarray, tneg, tadd, tminus, tmult, tdiv } types;

typedef union {
  int i;
  double d;
  char c;
  char b;
  char *s;
} uvalue;


typedef struct _node {
  types type;
  uvalue value;
  struct _node* l;
  struct _node* r;
} node;

int initNode(node **p);
int freeNode(node *n);
int isEqual(node* n, node *m);

node* intNode(const char *str);
node* doubleNode(const char *str);
node* addNode(node* const l, node* const r);
node* minusNode(node* const l, node* const r);
node* divNode(node* const l, node* const r);
node* multNode(node* const l, node* const r);
node* negNode(node* const l);

node* evalNode(const node* root);
void printNode(node* n);

#endif
