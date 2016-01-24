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
  (*p)->type = tnull;
  return(0);
}



node* intNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = tint;

  n->value.i = atoi(str);

  return n;
}



node* doubleNode(const char *str){
  node *n;
  initNode(&n);

  n->l = NULL;
  n->r = NULL;
  n->type = tdouble;

  n->value.d = atof(str);

  return n;
}


node* addNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = tadd;

  return n;
}


node* minusNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = tminus;

  return n;
}

node* divNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = tdiv;

  return n;
}



node* multNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = tmult;

  return n;
}


node* negNode(node* const l){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = NULL;
  n->type = tneg;

  return n;
}


node* sumOverNode(node* const l){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = NULL;
  n->type = tsumover;

  return n;
}




node* drawNode(node* const l, node* const r){
  node *n;
  initNode(&n);

  n->l = l;
  n->r = r;
  n->type = tdraw;

  return n;
}


int _error(node **n, int errorcode) {
  (*n)->type = terror;
  return (*n)->value.i = errorcode;
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
  if(n->type == tci){
    col_int_free(n->value.ci);
  }
  free(n);
}

int _hasError(const node* n){
  return (n->type==terror);
}


node* _copyError(const node *in){
  node *out;
  initNode(&out);
  out->type = terror;
  out->value.i = in->value.i;
  return out;
}

void printNode(node* n){
  switch(n->type){
    case tadd:
      printNode(n->l);
      printf("+");
      printNode(n->r);
    break;
    case tminus:
      printNode(n->l);
      printf("-");
      printNode(n->r);
    break;
    case tmult:
      printNode(n->l);
      printf("*");
      printNode(n->r);
    break;
    case tdiv:
      printNode(n->l);
      printf("/");
      printNode(n->r);
    break;
    case tint:
        printf("%d",n->value.i);
    break;
    case tdouble:
        printf("%f",n->value.d);
    break;
    case tci:
        col_int_disp(n->value.ci);
    break;
    case terror:
        printf("error: %s\n",lpl_error[n->value.i]);
    break;
    default:
      dbg("%s","Error evaluating expression.");
  }
}


node* _add(const node* l, const node* r){
  node *out;
  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}
  initNode(&out);
  switch(l->type){
    case tint:
      switch(r->type){
        case tint:
          out->type = tint;
          out->value.i = l->value.i+r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
          out->value.d = l->value.i+r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          out->type = tdouble;
          out->value.d = l->value.d+r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
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
  if(l->type==tint){
      dbg("%s\n","Negate on int.");
      out->type=l->type;
      out->value.i = -l->value.i;
  }
  else if(l->type==tdouble){
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
    case tint:
      switch(r->type){
        case tint:
          out->type = tint;
          out->value.i = l->value.i-r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
          out->value.d = l->value.i-r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          out->type = tdouble;
          out->value.d = l->value.d-r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
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
    case tint:
      switch(r->type){
        case tint:
          out->type = tint;
          out->value.i = l->value.i*r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
          out->value.d = l->value.i*r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          out->type = tdouble;
          out->value.d = l->value.d*r->value.i;
        break;
        case tdouble:
          out->type = tdouble;
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

  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}


  initNode(&out);
  switch(l->type){
    case tint:
      switch(r->type){
        case tint:
          out->type = tci;
          col_int_init(&out->value.ci);
          col_int_rand(out->value.ci,NULL,0,r->value.i,l->value.i);
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
  if( _hasError(l)) {out = _copyError(l); return out;}
  initNode(&out);
  switch(l->type){
    case tint:
      dbg("%s\n","sumover on int.");
      out->type=l->type;
      out->value.i = l->value.i;
    break;
    case tdouble:
      dbg("%s\n","sumover on double.");
      out->type=l->type;
      out->value.d = l->value.d;
    break;
    case tci:
      dbg("%s\n","sumover on signed integer array.");
      out->type=tint;
      col_int_init(&out->value.ci);
      col_int_sum(l->value.ci,&out->value.i);
    break;
    default:
      _error(&out,LPL_INVALIDARGS_ERROR);
    break;
  }
  return(out);
}








node* _equal(const node* l, const node* r){
  node *out;

  if( _hasError(l)) {out = _copyError(l); return out;}
  if( _hasError(r)) {out = _copyError(r); return out;}

  initNode(&out);
  switch(l->type){
    case tint:
      switch(r->type){
        case tint:
          out->type = tboolean;
          out->value.b = l->value.i==r->value.i;
        break;
        case tdouble:
          out->type = tboolean;
          out->value.b = l->value.i==r->value.d;
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          out->type = tboolean;
          out->value.b = l->value.d==r->value.i;
        break;
        case tdouble:
          out->type = tboolean;
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
    case tint:
      switch(r->type){
        case tint:
          if(r->value.i==0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else{
            out->type = tdouble;
            out->value.d = ((double)l->value.i)/((double)r->value.i);
          }
        break;
        case tdouble:
          if(r->value.d==0.0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else {
            out->type = tdouble;
            out->value.d = l->value.i/r->value.d;
          }
        break;
        default:
          _error(&out,LPL_INVALIDARGS_ERROR);
        break;

      }
    break;
    case tdouble:
      switch(r->type){
        case tint:
          if(r->value.i==0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else{
            out->type = tdouble;
            out->value.d = l->value.d/r->value.i;
          }
        break;
        case tdouble:
          if(r->value.d==0.0){
            _error(&out,LPL_DIVBYZERO_ERROR);
          }
          else {
            out->type = tdouble;
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
    case tneg:
      dbg("%s","Evaluating add.\n");
      out = _neg(l=evalNode(n->l));
      freeNode(l); 
    break;
    case tadd:
      dbg("%s","Evaluating add.\n");
      out = _add(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case tminus:
      dbg("%s","Evaluating minus.\n");
      out = _minus(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case tmult:
      dbg("%s","Evaluating mult.\n");
      out = _mult(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case tdiv:
      dbg("%s","Evaluating div.\n");
      out = _div(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case tint:
       dbg("%s","Evaluating int.\n");
       initNode(&out);
       memcpy(out,n,sizeof(node));
    break;
    case tdouble:
       dbg("%s","Evaluating double.\n");
       initNode(&out);
       memcpy(out,n,sizeof(node));
    break;
    case tdraw:
      dbg("%s","Evaluating draw.\n");
      out = _draw(l=evalNode(n->l),r=evalNode(n->r));
      freeNode(l); freeNode(r);
    break;
    case tsumover:
      dbg("%s","Evaluating sum over.\n");
      out = _sumover(l=evalNode(n->l));
      freeNode(l);
    break;
    case terror:
       dbg("%s","Evaluating error.\n");
       n = out;
    break;
    default:
      dbg("%s","Error evaluating expression.");
  }
  return out;

}

int isEqual(node* n, node *m){
  node *c;
  int val;

  val = 0;
  if((c = _equal(n,m))->type==tboolean){
    val = c->value.b;
  }
  freeNode(c);
  return val;
}

