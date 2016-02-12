#ifndef NODE_H
#define NODE_H

#include "libcol/col.h"


typedef enum {
    /* Scalar types */
    tnull,
    tboolean,
    tint,
    tdouble,
    tchar,
    terror,
    tarray,
    tneg,
    tadd,
    tminus,
    tmult,
    tdiv,
    /* Array functions */
    tdraw,
    tsumover,
    tbang,
    teq,
    /* Array types */
    tci,
    tcui
} types;

typedef struct _error_value {
  int error_code;
  const char *error_string;
} error_value;

typedef union {
  int i;
  double d;
  char c;
  char b;
  char *s;
  error_value e;

  col_int *ci;
  col_uint *cui;
} uvalue;



typedef struct _node {
  types type;
  uvalue value;
  struct _node* l;
  struct _node* r;
} node;

int initNode(node **p);
int freeNode(node *n);

node* intNode(const char *str);
node* doubleNode(const char *str);
node* addNode(node* const l, node* const r);
node* minusNode(node* const l, node* const r);
node* divNode(node* const l, node* const r);
node* multNode(node* const l, node* const r);
node* drawNode(node* const l, node* const r);
node* eqNode(node* const l, node* const r);
node* sumOverNode(node* const r);
node* bangNode(node* const l);
node* negNode(node* const l);

node* evalNode(const node* root);
void printNode(node* n);

#endif
