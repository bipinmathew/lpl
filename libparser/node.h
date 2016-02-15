#ifndef NODE_H
#define NODE_H

#include "libcol/col.h"


typedef enum {
    /* Scalar types */
    scalar_null_node,
    scalar_boolean_node,
    scalar_int_node,
    scalar_double_node,
    scalar_char_node,
    scalar_error_node,
    /* Array types */
    vector_int_node,
    vector_uint_node,
    /* Functions */
    neg_node,
    add_node,
    minus_node,
    mult_node,
    div_node,
    /* Array functions */
    draw_node,
    sumover_node,
    bang_node,
    eq_node
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

  col_int *vector_int;
  col_uint *vector_uint;
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
