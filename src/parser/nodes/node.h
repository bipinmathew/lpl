#ifndef NODE_H
#define NODE_H


typedef enum { tnull, tint, tdouble, tchar, terror, tarray, tadd, tminus, tmult, tdiv } types;

typedef union {
  int i;
  double d;
  char c;
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
node* newNode(const char *str,types type, node* const l, node* const r);
node* evalNode(const node* root);
void printNode(node* n);

#endif
