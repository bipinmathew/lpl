#ifndef NODE_H
#define NODE_H

#include "libcol/col.h"
#include "lpl_errors.h"
#include "trie.h"
#include "queue.h"

#define LPL_MAX_NUM_ARGS 20


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
    vector_double_node,
    vector_uint_node,
    /* Identifier node */
    ident_node,
    /* Functions */
    assign_node,
    neg_node,
    add_node,
    sub_node,
    mult_node,
    div_node,
    function_definition_node,
    /* Array functions */
    draw_node,
    sumover_node,
    bang_node,
    /* Comparison functions */
    eq_node,
    lt_node,
    gt_node,
    lteq_node,
    gteq_node
} types;

typedef struct _error_value {
  int error_code;
  const char *error_string;
} lpl_error;

typedef union {
  int scalar_int;
  double scalar_double;
  char b;
  char *s;
  lpl_error e;

  col_int *vector_int;
  col_double *vector_double;
  col_uint *vector_uint;
  Queue *statement_list;
} uvalue;



typedef struct _node {
  types type;
  uvalue value;
  unsigned int num_children;
  struct _node* child[LPL_MAX_NUM_ARGS];
  int ref;
} node;

int initDyadicNode(node **p, node *l, node *r, types node_type);
int retainNode(node **p);
int releaseNode(node **n);

/* Include all actual computation types. */

node* eval_assign_node(const node* l, node* r, Trie *scope);
node* eval_neg_node(const node* l, Trie *scope);

node* eval_add_node(const node* l, const node* r, Trie *scope);
node* eval_sub_node(const node* l, const node* r, Trie *scope);
node* eval_mult_node(const node* l, const node* r, Trie *scope);
node* eval_div_node(const node* l, const node* r, Trie *scope);


node* eval_draw_node(const node* l, const node* r, Trie *scope);
node* eval_sumover_node(const node* l, Trie *scope);
node* eval_bang_node(const node* l, Trie *scope);

node* eval_eq_node(const node* l, const node* r, Trie *scope);
node* eval_lt_node(const node* l, const node* r, Trie *scope);
node* eval_gt_node(const node* l, const node* r, Trie *scope);
node* eval_lteq_node(const node* l, const node* r, Trie *scope);
node* eval_gteq_node(const node* l, const node* r, Trie *scope);
/* End actuall computation types. */




node* intNode(const char *str);
node* doubleNode(const char *str);
node* identNode(const char *str);
node* addNode(node* const l, node* const r);
node* subNode(node* const l, node* const r);
node* divNode(node* const l, node* const r);
node* multNode(node* const l, node* const r);
node* drawNode(node* const l, node* const r);

node* functionDefinitionNode(Queue* const l);

node* eqNode(node* const l, node* const r);
node* ltNode(node* const l, node* const r);
node* gtNode(node* const l, node* const r);
node* lteqNode(node* const l, node* const r);
node* gteqNode(node* const l, node* const r);


node* sumOverNode(node* const r);
node* bangNode(node* const l);
node* negNode(node* const l);


node* identNode(const char *str);
node* assignNode(node* const l, node* const r);

node* evalNode(node* root,Trie *scope);
void printNode(node* n, Trie *scope);

/* TODO Figure out how to hide this function appropriatly. 
   Perhaps put it in a node-private.h file only visible from the libparser
   library? */

lpl_error_code lpl_expand_node(const node* in, const node** out, Trie *scope);

/* TODO Figure out a way to get rid of these functions.. */
int lpl_make_error_node(node *n, lpl_error_code errorcode, const char *err);
int lpl_make_error(lpl_error **error,lpl_error_code errorcode, const char *err);
int lpl_is_error_node(const node* n);
node* lpl_copy_error(const node *in);
/* End crappy code.. */

#endif
