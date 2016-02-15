#include "node.h"
#include "lpl_errors.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initNode(node **p){
  if((*p = (node *) malloc(sizeof(node)))==NULL){
    return(1);
  }
  (*p)->l = NULL;
  (*p)->r = NULL;
  (*p)->type = scalar_null_node;
  return(0);
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



node* doubleNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = scalar_double_node;

  n->value.d = atof(str);

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


node* errorNode(int errorcode){
  node *n;
  initNode(&n);
  _error(&n,errorcode);
}

int freeNode(node *n){
  if(n->l != NULL)
    freeNode(n->l);
  if(n->r != NULL)
    freeNode(n->r);
  if(n->type == vector_scalar_int_node){
    col_int_free(n->value.ci);
  }
  free(n);
}

int _hasError(const node* n){
  return (n->type==scalar_error_node);
}


node* _copyError(const node *in){
  node *out;
  initNode(&out);
  out->type = scalar_error_node;
  out->value.e.error_code = in->value.e.error_code;
  out->value.e.error_string = in->value.e.error_string;
  return out;
}

void printNode(node* n){
  switch(n->type){
    case add_node:
      printNode(n->l);
      printf("+");
      printNode(n->r);
    break;
    case minus_node:
      printNode(n->l);
      printf("-");
      printNode(n->r);
    break;
    case mult_node:
      printNode(n->l);
      printf("*");
      printNode(n->r);
    break;
    case div_node:
      printNode(n->l);
      printf("/");
      printNode(n->r);
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
    case vector_scalar_int_node:
        col_int_disp(n->value.ci);
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


node* _add(const node* l, const node* r){
  node *out;
  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}
  initNode(&out);
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
  }
  return(out);
}

node* _neg(const node* l){
  node *out;
  if( _hasError(l)) {out = _copyError(l); return out;}
  initNode(&out);
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



node* _minus(const node* l, const node* r){
  node *out;
  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}

  initNode(&out);
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
  }
  return(out);
}


node* _mult(const node* l, const node* r){
  node *out;

  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}


  initNode(&out);
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
  }
  return(out);
}

node* _draw(const node* l, const node* r){
  node *out;
  col_error e;

  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}


  initNode(&out);
  switch(l->type){
    case scalar_int_node:
      switch(r->type){
        case scalar_int_node:
          out->type = vector_scalar_int_node;
          if(NO_ERROR!=(e=col_int_init(&out->value.ci))){
            _error(&out,LPL_CUSTOM_ERROR);
          }
          else{
            if(NO_ERROR!=(e=col_int_rand(out->value.ci,NULL,0,r->value.i,l->value.i))){
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


node* _sumover(const node* l){
  node *out;
  col_error e;
  if( _hasError(l)) {out = _copyError(l); return out;}
  initNode(&out);
  switch(l->type){
    case vector_scalar_int_node:
      dbg("%s\n","sumover on signed integer array.");
      out->type=scalar_int_node;
      col_int_sum(l->value.ci,&out->value.i);
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}


node* _bang(const node* l){
  node *out;
  col_error e;
  if( _hasError(l)) {out = _copyError(l); return out;}
  initNode(&out);
  switch(l->type){
    case scalar_int_node:
      dbg("%s\n","bang on integer.");
      out->type=vector_scalar_int_node;
      if(NO_ERROR!=(e=col_int_init(&out->value.ci))){
        _error(&out,LPL_CUSTOM_ERROR);
      }
      else{
        if(NO_ERROR!=(e=col_int_range(out->value.ci,0,l->value.i, (l->value.i > 0) ? 1 : -1 ))){
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


node* _eq(const node* l, const node* r){
  node *out;

  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}

  initNode(&out);
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
  }
  return(out);
}


node* _div(const node* l, const node* r){
  node *out;
  if( _hasError(l)) { out = _copyError(l); return out; };
  if( _hasError(r)) { out = _copyError(r); return out; };

  initNode(&out);
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
  }
  return(out);
}


node* evalNode(const node* n){
  node *out;
  node *l,*r;
  switch(n->type){
    case neg_node:
      dbg("%s","Evaluating add.\n");
      out = _neg(l=evalNode(n->l));
      freeNode(l); 
    break;
    case add_node:
      dbg("%s","Evaluating add.\n");
      out = _add(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case minus_node:
      dbg("%s","Evaluating minus.\n");
      out = _minus(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case mult_node:
      dbg("%s","Evaluating mult.\n");
      out = _mult(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case div_node:
      dbg("%s","Evaluating div.\n");
      out = _div(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case eq_node:
      dbg("%s","Evaluating eq.\n");
      out = _eq(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
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
      out = _draw(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case sumover_node:
      dbg("%s","Evaluating sum over.\n");
      out = _sumover(l=evalNode(n->l));
      freeNode(l);
    break;
    case bang_node:
      dbg("%s","Evaluating bang.\n");
      out = _bang(l=evalNode(n->l));
      freeNode(l);
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

