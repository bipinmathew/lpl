#include "node.h"
#include "lpl_errors.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libcalg-1.0/libcalg/trie.h>



static node* eval_assign_node(const node* l, node* r, Trie *scope);
static node* eval_neg_node(const node* l, Trie *scope);

node* eval_add_node(const node* l, const node* r, Trie *scope);
node* eval_sub_node(const node* l, const node* r, Trie *scope);
node* eval_mult_node(const node* l, const node* r, Trie *scope);
node* eval_div_node(const node* l, const node* r, Trie *scope);


static node* eval_draw_node(const node* l, const node* r, Trie *scope);
static node* eval_sumover_node(const node* l, Trie *scope);
static node* eval_bang_node(const node* l, Trie *scope);
static node* eval_eq_node(const node* l, const node* r, Trie *scope);



int initNode(node **p, node *l, node *r, types node_type){
  if((*p = (node *) malloc(sizeof(node)))==NULL){
    return(1);
  }
  (*p)->ref = 0;
  (*p)->l = l;
  (*p)->r = r;
  (*p)->type = node_type;
  retainNode(p);
  return(0);
}


node* intNode(const char *str){
  node *n;
  initNode(&n, NULL, NULL, vector_int_node);

  col_int_init_scalar(&n->value.vector_int,atoi(str));

  return n;
}


node* identNode(const char *str){
  node *n;
  initNode(&n, NULL, NULL, ident_node);

  n->value.s=strndup(str,strlen(str));

  return n;
}




node* doubleNode(const char *str){
  node *n;
  initNode(&n, NULL, NULL, vector_double_node);

  col_double_init_scalar(&n->value.vector_double,atof(str));

  return n;
}



node* assignNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, assign_node);

  return n;
}


node* addNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, add_node);
  return n;
}


node* subNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, sub_node);

  return n;
}

node* divNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, div_node);

  return n;
}

node* multNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, mult_node);

  return n;
}

/* Comparison Nodes */

node* eqNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, eq_node);

  return n;
}

node* ltNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, lt_node);

  return n;
}

node* gtNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, gt_node);

  return n;
}


node* lteqNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, lteq_node);

  return n;
}

node* gteqNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, gteq_node);

  return n;
}

/* End Comparison Nodes */

node* negNode(node* const l){
  node *n;
  initNode(&n, l, NULL, neg_node);

  return n;
}


node* sumOverNode(node* const l){
  node *n;
  initNode(&n, l, NULL, sumover_node);

  return n;
}



node* bangNode(node* const l){
  node *n;
  initNode(&n, l, NULL, bang_node);

  return n;
}

node* drawNode(node* const l, node* const r){
  node *n;
  initNode(&n, l, r, draw_node);

  return n;
}

int lpl_error(node **n, lpl_error_code errorcode, const char *err) {
  (*n)->type = scalar_error_node;
  if( LPL_CUSTOM_ERROR == ((*n)->value.e.error_code = errorcode)){
    (*n)->value.e.error_string = err;
  }
  return 0;
}

int retainNode(node **p){
  (*p)->ref++;
  dbg("retainNode called on node of type: %d now: %d \n",(*p)->type,(*p)->ref);
  return 0;
}

int releaseNode(node *n){

  if(n->l != NULL)
    releaseNode(n->l);
  if(n->r != NULL)
    releaseNode(n->r);

  n->ref--;

  dbg("releaseNode called on node of type: %d now: %d \n",n->type,n->ref);
  if(n->ref==0){
    switch(n->type){
      case vector_int_node:
        col_int_free(n->value.vector_int);
        break;
      case vector_uint_node:
        col_uint_free(n->value.vector_uint);
        break;
      case ident_node:
        free(n->value.s);
        break;
    }
    free(n);
  }
  return(0);
}

int _has_error(const node* n){
  return (n->type==scalar_error_node);
}


node* _copy_error(const node *in){
  node *out;
  initNode(&out, NULL, NULL, scalar_error_node);

  out->value.e.error_code = in->value.e.error_code;
  out->value.e.error_string = in->value.e.error_string;
  return out;
}

void printNode(node* n, Trie *scope){
  TrieValue  sym_val;
  switch(n->type){
    case add_node:
      printf("+");
    break;
    case sub_node:
      printf("-");
    break;
    case mult_node:
      printf("*");
    break;
    case div_node:
      printf("/");
    break;
    case ident_node:
      dbg("%s","Printing ident_node...\n");
      if(TRIE_NULL==(sym_val=trie_lookup(scope,n->value.s))){
        printf("undefined variable %s\n",n->value.s);
      } else {
        printNode((node *)sym_val,scope);
      }
    break;
    case scalar_int_node:
        printf("%d",n->value.scalar_int);
    break;
    case scalar_double_node:
        printf("%f",n->value.scalar_double);
    break;
    case scalar_boolean_node:
        printf("%d",n->value.b);
    break;
    case vector_int_node:
        col_int_disp(n->value.vector_int);
    break;
    case vector_uint_node:
        col_uint_disp(n->value.vector_uint);
    break;
    case scalar_error_node:
        if(n->value.e.error_code == LPL_CUSTOM_ERROR){
          printf("%s\n",n->value.e.error_string);
        }
        else{
          printf("%s\n",lpl_error_string[n->value.e.error_code]);
        }
    break;
    default:
      dbg("%s","Error printing expression.");
  }
}



int _expand_node(const node* in, const node** out, Trie *scope){
  TrieValue  sym_val;
  *out = in;
  if(in->type==ident_node){
    if(TRIE_NULL==(sym_val=trie_lookup(scope,in->value.s))){
        return LPL_UNDEFINED_VAR_ERROR;
    } else {
      *out=(node *)sym_val;
    }
  }
  return 0;
}



static node* eval_assign_node(const node* l, node* r, Trie *scope){
  TrieValue  sym_val;

  if(TRIE_NULL!=(sym_val=trie_lookup(scope,l->value.s))){
    releaseNode((node*)sym_val);
  }

  trie_insert(scope,l->value.s,(TrieValue *)r);
  /* We need to keep both one reference in the tree and 
     one in the symbol table. */
  retainNode(&r);
  retainNode(&r);
  return r;
}



node* eval_neg_node(const node* l, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}

  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }

  if(l->type==scalar_int_node){
      dbg("%s\n","Negate on int.");
      out->type=l->type;
      out->value.scalar_int = -l->value.scalar_int;
  }
  else if(l->type==scalar_double_node){
      dbg("%s\n","Negate on double.");
      out->type=l->type;
      out->value.scalar_double = -l->value.scalar_double;
  }
  else{
     lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
  }

  return(out);
}


node* eval_draw_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  int lvalue, rvalue;

  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }



  

  switch(l->type){
    case vector_int_node:
      switch(r->type){
        case vector_int_node:
          out->type = vector_int_node;
          if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
           lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          else{
            col_int_get(l->value.vector_int,0,&lvalue); 
            col_int_get(r->value.vector_int,0,&rvalue); 
            if(LIBCOL_NO_ERROR!=(e=col_int_rand(out->value.vector_int,NULL,0,rvalue,lvalue))){
             lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
            }
          }
        break;
        default:
         lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
        break;

      }
    break;
    default:
     lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}


node* eval_sumover_node(const node* l, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}


  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }

  switch(l->type){
    case vector_int_node:
      dbg("%s\n","sumover on signed integer array.");
      out->type=scalar_int_node;
      col_int_sum(l->value.vector_int,&out->value.scalar_int);
    break;
    default:
     lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}


node* eval_bang_node(const node* l, Trie *scope){
  node *out;
  int result;
  col_error e;
  if( _has_error(l)) {out = _copy_error(l); return out;}

  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }

  switch(l->type){
    case scalar_int_node:
      dbg("%s\n","bang on integer.");
      out->type=vector_int_node;
      if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
       lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
      }
      else{
        if(LIBCOL_NO_ERROR!=(e=col_int_range(out->value.vector_int,0,l->value.scalar_int, (l->value.scalar_int > 0) ? 1 : -1 ))){
         lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
        }
      }
    break;
    default:
     lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}

static int eval_eq(double l, double r){
  return l==r;
}
static int eval_lt(double l, double r){
  return l<r;
}
static int eval_gt(double l, double r){
  return l>r;
}
static int eval_lteq(double l, double r){
  return l<=r;
}
static int eval_gteq(double l, double r){
  return l>=r;
}


static node* 
eval_cmp_node(
  const node* l, 
  const node* r, 
  Trie *scope,
  int (*scmp)(double l, double r),
  col_error (*svcmp)(const col_int * arr, col_uint * idx, int value),
  col_error (*vscmp)(const col_int * arr, col_uint * idx, int value)
  ){
  node *out;
  int result;
  col_error e;

  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
   lpl_error(&out,result,NULL);
    return out;
  }
  
  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_boolean_node;
          out->value.b = scmp(l->value.scalar_int,r->value.scalar_int);
        break;
        case scalar_double_node:
          out->type = scalar_boolean_node;
          out->value.b = scmp(l->value.scalar_int,r->value.scalar_double);
        break;
        case vector_int_node:
          out->type = vector_uint_node;
          if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){
           lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          //col_int_disp(r->value.vector_int);
          svcmp(r->value.vector_int, out->value.vector_uint , l->value.scalar_int);
        break;
        default:
         lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
        break;

      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_boolean_node;
          out->value.b = scmp(l->value.scalar_double,r->value.scalar_int);
        break;
        case scalar_double_node:
          out->type = scalar_boolean_node;
          out->value.b = scmp(l->value.scalar_double,r->value.scalar_double);
        break;
        default:
         lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
        break;
      }
    break;
    case vector_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = vector_uint_node;
          if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){
           lpl_error(&out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          //col_int_disp(l->value.vector_int);
          vscmp(l->value.vector_int, out->value.vector_uint , r->value.scalar_int);
        break;
        default:
         lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
        break;
      }
    break;
    default:
     lpl_error(&out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}

node* eval_eq_node(const node* l, const node* r, Trie *scope){
  return eval_cmp_node(l,r,scope,eval_eq,col_int_eq_scalar,col_int_eq_scalar);
}

node* eval_lt_node(const node* l, const node* r, Trie *scope){
  return eval_cmp_node(l,r,scope,eval_lt,col_int_gt_scalar,col_int_lt_scalar);
}

node* eval_gt_node(const node* l, const node* r, Trie *scope){
  return eval_cmp_node(l,r,scope,eval_gt,col_int_lt_scalar,col_int_gt_scalar);
}

node* eval_lteq_node(const node* l, const node* r, Trie *scope){
  return eval_cmp_node(l,r,scope,eval_lteq,col_int_gteq_scalar,col_int_lteq_scalar);
}

node* eval_gteq_node(const node* l, const node* r, Trie *scope){
  return eval_cmp_node(l,r,scope,eval_gteq,col_int_lteq_scalar,col_int_gteq_scalar);
}



node* evalNode(node* n,Trie *scope){
  node *out;
  node *l,*r;
  switch(n->type){
    case scalar_null_node:
      dbg("%s","Evaluating null_node.\n");
    break;
    case ident_node:
      dbg("%s","Evaluating ident_node.\n");
      out = n;
      retainNode(&out);
    break;
    case assign_node:
      dbg("%s","Evaluating assign.\n");
      out = eval_assign_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope),scope);
      releaseNode(l); releaseNode(r);
    break;
    case neg_node:
      dbg("%s","Evaluating neg.\n");
      out = eval_neg_node(l=evalNode(n->l,scope), scope);
      releaseNode(l); 
    break;
    case add_node:
      dbg("%s","Evaluating add.\n");
      out = eval_add_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope),scope);
      releaseNode(l); releaseNode(r);
    break;
    case sub_node:
      dbg("%s","Evaluating minus.\n");
      out = eval_sub_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case mult_node:
      dbg("%s","Evaluating mult.\n");
      out = eval_mult_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case div_node:
      dbg("%s","Evaluating div.\n");
      out = eval_div_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;

    case eq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_eq_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case lt_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_lt_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case gt_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_gt_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case lteq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_lteq_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case gteq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_gteq_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case scalar_int_node:
       dbg("%s","Evaluating int.\n");
       out = n;
       retainNode(&out);
    break;
    case scalar_double_node:
       dbg("%s","Evaluating double.\n");
       out = n;
       retainNode(&out);
    break;
    case vector_int_node:
       dbg("%s","Evaluating vector_int_node.\n");
       out = n;
       retainNode(&out);
    break;
    case vector_double_node:
       dbg("%s","Evaluating vector_double_node.\n");
       out = n;
       retainNode(&out);
    break;
    case draw_node:
      dbg("%s","Evaluating draw.\n");
      out = eval_draw_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
      releaseNode(l); releaseNode(r);
    break;
    case sumover_node:
      dbg("%s","Evaluating sum over.\n");
      out = eval_sumover_node(l=evalNode(n->l,scope), scope);
      releaseNode(l);
    break;
    case bang_node:
      dbg("%s","Evaluating bang.\n");
      out = eval_bang_node(l=evalNode(n->l,scope), scope);
      releaseNode(l);
    break;
    case scalar_error_node:
       dbg("%s","Evaluating error.\n");
       out=n;
       retainNode(&out);
    break;
    default:
      dbg("%s","Error evaluating expression.");
  }
  return out;
}

