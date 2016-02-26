#include "node.h"
#include "lpl_errors.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libcalg-1.0/libcalg/trie.h>

static int _error(node **n, int errorcode);
static int _has_error(const node* n);
static node* _copy_error(const node *in);

static int _copy_node(node *dest, const node* const src);

static node* eval_assign_node(const node* l, node* r, Trie *scope);
static node* eval_add_node(const node* l, const node* r, Trie *scope);
static node* eval_neg_node(const node* l, Trie *scope);
static node* eval_minus_node(const node* l, const node* r, Trie *scope);
static node* eval_mult_node(const node* l, const node* r, Trie *scope);
static node* eval_draw_node(const node* l, const node* r, Trie *scope);
static node* eval_sumover_node(const node* l, Trie *scope);
static node* eval_bang_node(const node* l, Trie *scope);
static node* eval_eq_node(const node* l, const node* r, Trie *scope);
static node* eval_div_node(const node* l, const node* r, Trie *scope);

static int _expand_node(const node* in, const node** out, Trie *scope);


int initNode(node **p){
  if((*p = (node *) malloc(sizeof(node)))==NULL){
    return(1);
  }
  (*p)->ref = 0;
  (*p)->l = NULL;
  (*p)->r = NULL;
  (*p)->type = scalar_null_node;
  retainNode(p);
  return(0);
}

int _copy_node(node *dest, const node* const src){
  initNode(&dest);
  memcpy(dest,src,sizeof(node));
  switch(dest->type){
  case vector_int_node:
    break;
  default:
    printf("No copy..\n");


  }

}



node* intNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = scalar_int_node;

  n->value.i = atoi(str);

  return n;
}


node* identNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = ident_node;

  n->value.s=strndup(str,strlen(str));

  return n;
}




node* doubleNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = scalar_double_node;

  n->value.d = atof(str);

  return n;
}



node* assignNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = assign_node;

  return n;
}




node* addNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = add_node;

  return n;
}


node* minusNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = minus_node;

  return n;
}

node* divNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = div_node;

  return n;
}

node* multNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = mult_node;

  return n;
}

node* eqNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = eq_node;

  return n;
}

node* negNode(node* const l){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = NULL;
  n->type = neg_node;

  return n;
}


node* sumOverNode(node* const l){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = NULL;
  n->type = sumover_node;

  return n;
}



node* bangNode(node* const l){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = NULL;
  n->type = bang_node;

  return n;
}

node* drawNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = draw_node;

  return n;
}

int _error(node **n, int errorcode) {
  (*n)->type = scalar_error_node;
  (*n)->value.e.error_code = errorcode;
  (*n)->value.e.error_string = "Hello world.";
  return 0;
}

int retainNode(node **p){
  ++(*p)->ref;
  return 0;
}

int releaseNode(node *n){
  if(n->l != NULL)
    releaseNode(n->l);
  if(n->r != NULL)
    releaseNode(n->r);
  if((n->ref--)==0){
    switch(n->type){
      case vector_int_node:
        col_int_free(n->value.vector_int);
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
  initNode(&out);
  out->type = scalar_error_node;
  out->value.e.error_code = in->value.e.error_code;
  out->value.e.error_string = in->value.e.error_string;
  return out;
}

void printNode(node* n, Trie *scope){
  TrieValue  sym_val;
  switch(n->type){
    case add_node:
      printNode(n->l,scope);
      printf("+");
      printNode(n->r,scope);
    break;
    case minus_node:
      printNode(n->l,scope);
      printf("-");
      printNode(n->r,scope);
    break;
    case mult_node:
      printNode(n->l,scope);
      printf("*");
      printNode(n->r,scope);
    break;
    case div_node:
      printNode(n->l,scope);
      printf("/");
      printNode(n->r,scope);
    break;
    case ident_node:
      if(TRIE_NULL==(sym_val=trie_lookup(scope,n->value.s))){
        printf("undefined variable %s\n",n->value.s);
      } else {
        printNode((node *)sym_val,scope);
      }
    break;
    case scalar_int_node:
        printf("%d",n->value.i);
    break;
    case scalar_double_node:
        printf("%f",n->value.d);
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
          printf("%s\n",lpl_error_strings[n->value.e.error_code]);
        }
    break;
    default:
      dbg("%s","Error printing expression.");
  }
}



static int _expand_node(const node* in, const node** out, Trie *scope){
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
  node *out;
  trie_insert(scope,l->value.s,(TrieValue *)r);
  retainNode(&r);
  // _copy_node(out,r);
  // return r;
}


node* eval_add_node(const node* l, const node* r, Trie *scope){
  TrieValue  sym_val;
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  
  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_int_node;
          out->value.i = l->value.i+r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.i+r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;
      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d+r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d+r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;

  }
  return(out);
}

node* eval_neg_node(const node* l, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }

  if(l->type==scalar_int_node){
      dbg("%s\n","Negate on int.");
      out->type=l->type;
      out->value.i = -l->value.i;
  }
  else if(l->type==scalar_double_node){
      dbg("%s\n","Negate on double.");
      out->type=l->type;
      out->value.d = -l->value.d;
  }
  else{
      _error(&out,LPL_INVALIDARGS_ERROR);
  }

  return(out);
}



node* eval_minus_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out);


  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  



  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_int_node;
          out->value.i = l->value.i-r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.i-r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d-r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d-r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* eval_mult_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;

  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}


  initNode(&out);


  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  


  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_int_node;
          out->value.i = l->value.i*r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.i*r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d*r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_double_node;
          out->value.d = l->value.d*r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}

node* eval_draw_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;

  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  

  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = vector_int_node;
          if(NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
            _error(&out,LPL_CUSTOM_ERROR);
          }
          else{
            if(NO_ERROR!=(e=col_int_rand(out->value.vector_int,NULL,0,r->value.i,l->value.i))){
              _error(&out,LPL_CUSTOM_ERROR);
            }
          }
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* eval_sumover_node(const node* l, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }

  switch(l->type){
    case vector_int_node:
      dbg("%s\n","sumover on signed integer array.");
      out->type=scalar_int_node;
      col_int_sum(l->value.vector_int,&out->value.i);
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* eval_bang_node(const node* l, Trie *scope){
  node *out;
  int result;
  col_error e;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }

  switch(l->type){
    case scalar_int_node:
      dbg("%s\n","bang on integer.");
      out->type=vector_int_node;
      if(NO_ERROR!=(e=col_int_init(&out->value.vector_int))){
        _error(&out,LPL_CUSTOM_ERROR);
      }
      else{
        if(NO_ERROR!=(e=col_int_range(out->value.vector_int,0,l->value.i, (l->value.i > 0) ? 1 : -1 ))){
          _error(&out,LPL_CUSTOM_ERROR);
        }
      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* eval_eq_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;

  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  



  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_boolean_node;
          out->value.b = l->value.i==r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_boolean_node;
          out->value.b = l->value.i==r->value.d;
        break;
        case vector_int_node:
          out->type = vector_uint_node;
          if(NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){
            _error(&out,LPL_CUSTOM_ERROR);
          }
          col_int_disp(r->value.vector_int);
          col_int_select_scalar (r->value.vector_int, out->value.vector_uint , l->value.i);
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          out->type = scalar_boolean_node;
          out->value.b = l->value.d==r->value.i;
        break;
        case scalar_double_node:
          out->type = scalar_boolean_node;
          out->value.b = l->value.d==r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;
      }
    break;
    case vector_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = vector_uint_node;
          if(NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){
            _error(&out,LPL_CUSTOM_ERROR);
          }
          col_int_disp(l->value.vector_int);
          col_int_select_scalar (l->value.vector_int, out->value.vector_uint , r->value.i);
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;
      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* eval_div_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  if( _has_error(l)) { out = _copy_error(l); return out; };
  if( _has_error(r)) { out = _copy_error(r); return out; };

  initNode(&out);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }
  



  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          if(r->value.i==0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else{
            out->type = scalar_double_node;
            out->value.d = ((double)l->value.i)/((double)r->value.i);
          }
        break;
        case scalar_double_node:
          if(r->value.d==0.0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else {
            out->type = scalar_double_node;
            out->value.d = l->value.i/r->value.d;
          }
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case scalar_double_node:
      switch(r->type){
        case scalar_int_node:
          if(r->value.i==0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else{
            out->type = scalar_double_node;
            out->value.d = l->value.d/r->value.i;
          }
        break;
        case scalar_double_node:
          if(r->value.d==0.0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else {
            out->type = scalar_double_node;
            out->value.d = l->value.d/r->value.d;
          }
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* evalNode(node* n,Trie *scope){
  node *out;
  node *l,*r;
  switch(n->type){

    case ident_node:
      dbg("%s","Evaluating ident_node.\n");
      out = n;
    break;
    case assign_node:
      dbg("%s","Evaluating assign.\n");
      eval_assign_node(n->l,out=evalNode(n->r,scope),scope);
      releaseNode(n->l); releaseNode(n->r);
    break;
    case neg_node:
      dbg("%s","Evaluating add.\n");
      out = eval_neg_node(l=evalNode(n->l,scope), scope);
      releaseNode(l); 
    break;
    case add_node:
      dbg("%s","Evaluating add.\n");
      out = eval_add_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope),scope);
      releaseNode(l); releaseNode(r);
    break;
    case minus_node:
      dbg("%s","Evaluating minus.\n");
      out = eval_minus_node(l=evalNode(n->l,scope),r=evalNode(n->r,scope), scope);
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
    case scalar_int_node:
       dbg("%s","Evaluating int.\n");
       initNode(&out);
       memcpy(out,n,sizeof(node));
    break;
    case scalar_double_node:
       dbg("%s","Evaluating double.\n");
       initNode(&out);
       memcpy(out,n,sizeof(node));
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
       n = out;
    break;
    default:
      dbg("%s","Error evaluating expression.");
  }
  return out;

}

