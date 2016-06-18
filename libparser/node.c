#include "node.h"
#include "lpl_errors.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"
#include "queue.h"

int initDyadicNode(node **p, node *l, node *r, types node_type){
  if((*p = (node *) malloc(sizeof(node)))==NULL){
    return(1);
  }
  (*p)->ref = 0;
  (*p)->num_children = 2;
  (*p)->child[0] = l;
  (*p)->child[1] = r;
  (*p)->type = node_type;
  retainNode(p);
  return(0);
}


node* intNode(const char *str){
  node *n;
  initDyadicNode(&n, NULL, NULL, vector_int_node);

  col_int_init_scalar(&n->value.vector_int,atoi(str));

  return n;
}


node* identNode(const char *str){
  node *n;
  initDyadicNode(&n, NULL, NULL, ident_node);

  n->value.s=strndup(str,strlen(str));

  return n;
}




node* doubleNode(const char *str){
  node *n;
  initDyadicNode(&n, NULL, NULL, vector_double_node);

  col_double_init_scalar(&n->value.vector_double,atof(str));

  return n;
}



node* assignNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, assign_node);

  return n;
}


node* addNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, add_node);
  return n;
}


node* subNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, sub_node);

  return n;
}

node* divNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, div_node);

  return n;
}

node* multNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, mult_node);

  return n;
}

/* Comparison Nodes */

node* eqNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, eq_node);

  return n;
}

node* ltNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, lt_node);

  return n;
}

node* gtNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, gt_node);

  return n;
}


node* lteqNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, lteq_node);

  return n;
}

node* gteqNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, gteq_node);

  return n;
}

/* End Comparison Nodes */

node* negNode(node* const l){
  node *n;
  initDyadicNode(&n, l, NULL, neg_node);

  return n;
}


node* sumOverNode(node* const l){
  node *n;
  initDyadicNode(&n, l, NULL, sumover_node);

  return n;
}



node* bangNode(node* const l){
  node *n;
  initDyadicNode(&n, l, NULL, bang_node);

  return n;
}

node* drawNode(node* const l, node* const r){
  node *n;
  initDyadicNode(&n, l, r, draw_node);

  return n;
}



node* functionDefinitionNode(Queue* const l){
  node *n;
  n = (node *)malloc(sizeof(node));

  n->ref = 0;
  n->num_children = 1;
  n->type = function_definition_node;
  n->value.statement_list = l;
  retainNode(&n);
  return n;
}


int lpl_make_error_node(node *n, lpl_error_code errorcode, const char *err) {
  dbg("Inside lpl_make_error. Error code: %d",errorcode);
  assert(errorcode >= 0);
  n->type = scalar_error_node;
  if( LPL_CUSTOM_ERROR == (n->value.e.error_code = errorcode)){
    n->value.e.error_string = err;
  }
  return 0;
}

int lpl_make_error(lpl_error **error,lpl_error_code errorcode, const char *err){
  *error = (lpl_error*)malloc(sizeof(lpl_error));
  if( LPL_CUSTOM_ERROR == ((*error)->error_code = errorcode)){
    (*error)->error_string = err;
  }
  return 0;
}


int retainNode(node **p){
  (*p)->ref++;
  dbg("retainNode called on node of type: %d now: %d \n",(*p)->type,(*p)->ref);
  return 0;
}

int releaseNode(node **p){

  unsigned int i;

  for(i=0;i<(*p)->num_children;i++){
    if((*p)->child[i] != NULL)
      releaseNode(&(*p)->child[i]);
  }


  (*p)->ref--;

  dbg("releaseNode called on node of type: %d now: %d \n",(*p)->type,(*p)->ref);
  if((*p)->ref==0){
    switch((*p)->type){
      case vector_int_node:
        col_int_free((*p)->value.vector_int);
        break;
      case vector_uint_node:
        col_uint_free((*p)->value.vector_uint);
        break;
      case ident_node:
        free((*p)->value.s);
        break;
      default:
        break;
    }
    free(*p);
  }
  return(0);
}

int lpl_is_error_node(const node* n){
  return (n->type==scalar_error_node);
}


node* lpl_copy_error(const node *in){
  node *out;
  initDyadicNode(&out, NULL, NULL, scalar_error_node);

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
    case scalar_boolean_node:
        printf("%d",n->value.b);
    break;
    case vector_int_node:
        col_int_disp(n->value.vector_int);
    break;
    case vector_double_node:
        col_double_disp(n->value.vector_double);
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



lpl_error_code lpl_expand_node(const node* in, const node** out, Trie *scope){
  TrieValue  sym_val;
  *out = in;
  if(in->type==ident_node){
    if(TRIE_NULL==(sym_val=trie_lookup(scope,in->value.s))){
        return LPL_UNDEFINED_VAR_ERROR;
    } else {
      *out=(node *)sym_val;
    }
  }
  return LPL_NO_ERROR;
}



node* eval_assign_node(const node* l, node* r, Trie *scope){
  TrieValue  sym_val;
  node *p;

  if(TRIE_NULL!=(sym_val=trie_lookup(scope,l->value.s))){
    p=(node*)sym_val;
    releaseNode(&p);
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
  unsigned int llength,allocate,i;
  int result;
  col_error e;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}


  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }

  switch(l->type){
    case vector_int_node:
      dbg("%s\n","Negate on int.");

      initDyadicNode(&out, NULL, NULL, vector_int_node);
      if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
       lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
      }
      else{
        col_int_length(l->value.vector_int,&llength);
        allocate = llength;
        if(LIBCOL_NO_ERROR != (e = col_int__realloc(out->value.vector_int,&allocate))){
          lpl_make_error_node(out,e,NULL);
        }

        else{
          for(i=0;i<llength;i++){
            out->value.vector_int->d[i]=-l->value.vector_int->d[i];
          }
        }
        col_int__setlength(out->value.vector_int,llength);
      }
    break;
    case vector_double_node:
      dbg("%s\n","Negate on double.");

      initDyadicNode(&out, NULL, NULL, vector_double_node);
      if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){
       lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
      }
      else{
        col_double_length(l->value.vector_double,&llength);
        allocate = llength;
        if(LIBCOL_NO_ERROR != (e = col_double__realloc(out->value.vector_double,&allocate))){
          lpl_make_error_node(out,e,NULL);
        }

        else{
          for(i=0;i<llength;i++){
            out->value.vector_double->d[i]=-l->value.vector_double->d[i];
          }
        }
        col_double__setlength(out->value.vector_double,llength);
      }
    break;
    default: 
      lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}


node* eval_draw_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  int lvalue, rvalue;

  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}

  initDyadicNode(&out, NULL, NULL, scalar_null_node);

  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }
  if(LPL_NO_ERROR != (result=lpl_expand_node(r,&r,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }
  
  switch(l->type){
    case vector_int_node:
      switch(r->type){
        case vector_int_node:
          out->type = vector_int_node;
          if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
           lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          else{
            col_int_get(l->value.vector_int,0,&lvalue); 
            col_int_get(r->value.vector_int,0,&rvalue); 
            if(LIBCOL_NO_ERROR!=(e=col_int_rand(out->value.vector_int,NULL,0,rvalue,lvalue))){
             lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
            }
          }
        break;
        default:
         lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
        break;

      }
    break;
    default:
     lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}


node* eval_sumover_node(const node* l, Trie *scope){
  node *out;
  int result;
  union {int i; double d;} value;
  // int value;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}

  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }

  switch(l->type){
    case vector_int_node:
      dbg("%s\n","sumover on signed integer array.");
      initDyadicNode(&out, NULL, NULL, vector_int_node);
      col_int_sum(l->value.vector_int,&value.i);
      col_int_init_scalar(&out->value.vector_int,value.i);
    break;
    case vector_double_node:
      dbg("%s\n","sumover on signed double array.");
      initDyadicNode(&out, NULL, NULL, vector_double_node);
      col_double_sum(l->value.vector_double,&value.d);
      col_double_init_scalar(&out->value.vector_double,value.d);
    break;
    default:
     lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
}


node* eval_bang_node(const node* l, Trie *scope){
  node *out;
  int result;
  col_error e;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}

  initDyadicNode(&out, NULL, NULL, scalar_null_node);

  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }

  switch(l->type){
    case scalar_int_node:
      dbg("%s\n","bang on integer.");
      out->type=vector_int_node;
      if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
       lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
      }
      else{
        if(LIBCOL_NO_ERROR!=(e=col_int_range(out->value.vector_int,0,l->value.scalar_int, (l->value.scalar_int > 0) ? 1 : -1 ))){
         lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
        }
      }
    break;
    default:
     lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
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

  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}

  initDyadicNode(&out, NULL, NULL, scalar_null_node);

  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
   lpl_make_error_node(out,result,NULL);
    return out;
  }
  if(LPL_NO_ERROR != (result=lpl_expand_node(r,&r,scope))){
   lpl_make_error_node(out,result,NULL);
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
           lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          //col_int_disp(r->value.vector_int);
          svcmp(r->value.vector_int, out->value.vector_uint , l->value.scalar_int);
        break;
        default:
         lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
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
         lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
        break;
      }
    break;
    case vector_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = vector_uint_node;
          if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){
           lpl_make_error_node(out,LPL_CUSTOM_ERROR,col_error_strings[e]);
          }
          //col_int_disp(l->value.vector_int);
          vscmp(l->value.vector_int, out->value.vector_uint , r->value.scalar_int);
        break;
        default:
         lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
        break;
      }
    break;
    default:
     lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
    break;
  }
  return(out);
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
      out = eval_assign_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope),scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case function_definition_node:
      dbg("%s","Evaluating function definition.\n");
      return(n);
    break;
    case neg_node:
      dbg("%s","Evaluating neg.\n");
      out = eval_neg_node(l=evalNode(n->child[0],scope), scope);
      releaseNode(&l); 
    break;
    case add_node:
      dbg("%s","Evaluating add.\n");
      out = eval_add_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope),scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case sub_node:
      dbg("%s","Evaluating minus.\n");
      out = eval_sub_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case mult_node:
      dbg("%s","Evaluating mult.\n");
      out = eval_mult_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case div_node:
      dbg("%s","Evaluating div.\n");
      out = eval_div_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;

    case eq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_eq_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case lt_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_lt_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case gt_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_gt_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case lteq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_lteq_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case gteq_node:
      dbg("%s","Evaluating eq.\n");
      out = eval_gteq_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
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
      out = eval_draw_node(l=evalNode(n->child[0],scope),r=evalNode(n->child[1],scope), scope);
      releaseNode(&l); releaseNode(&r);
    break;
    case sumover_node:
      dbg("%s","Evaluating sum over.\n");
      out = eval_sumover_node(l=evalNode(n->child[0],scope), scope);
      releaseNode(&l);
    break;
    case bang_node:
      dbg("%s","Evaluating bang.\n");
      out = eval_bang_node(l=evalNode(n->child[0],scope), scope);
      releaseNode(&l);
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

