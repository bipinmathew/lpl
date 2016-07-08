#include <stdlib.h>
#include "node.h"
#include "lpl_errors.h"

static lpl_error_code eval_vivi_div(col_double *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_div(col_double *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_div(col_double *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_div(col_double *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_add(col_int *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_add(col_double *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_add(col_double *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_add(col_double *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_sub(col_int *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_sub(col_double *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_sub(col_double *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_sub(col_double *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_mult(col_int *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_mult(col_double *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_mult(col_double *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_mult(col_double *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);


#include"arithmetic.inl"

node* eval_div_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  lpl_error eval_error;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}


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
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_div(out->value.vector_double, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_div(out->value.vector_double, l->value.vector_int, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      default:
        lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
      break;
    }
  break;
  case vector_double_node:
    switch(r->type){
      case vector_int_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_div(out->value.vector_double, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_div(out->value.vector_double, l->value.vector_double, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
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
node* eval_add_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  lpl_error eval_error;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}


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
        initDyadicNode(&out,NULL,NULL,vector_int_node);
        if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_add(out->value.vector_int, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_add(out->value.vector_double, l->value.vector_int, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      default:
        lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
      break;
    }
  break;
  case vector_double_node:
    switch(r->type){
      case vector_int_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_add(out->value.vector_double, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_add(out->value.vector_double, l->value.vector_double, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
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
node* eval_sub_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  lpl_error eval_error;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}


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
        initDyadicNode(&out,NULL,NULL,vector_int_node);
        if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_sub(out->value.vector_int, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_sub(out->value.vector_double, l->value.vector_int, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      default:
        lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
      break;
    }
  break;
  case vector_double_node:
    switch(r->type){
      case vector_int_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_sub(out->value.vector_double, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_sub(out->value.vector_double, l->value.vector_double, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
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
node* eval_mult_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  lpl_error eval_error;
  if( lpl_is_error_node(l)) {out = lpl_copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = lpl_copy_error(r); return out;}


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
        initDyadicNode(&out,NULL,NULL,vector_int_node);
        if(LIBCOL_NO_ERROR!=(e=col_int_init(&out->value.vector_int))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_mult(out->value.vector_int, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_mult(out->value.vector_double, l->value.vector_int, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      default:
        lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);
      break;
    }
  break;
  case vector_double_node:
    switch(r->type){
      case vector_int_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_mult(out->value.vector_double, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_double_node);
        if(LIBCOL_NO_ERROR!=(e=col_double_init(&out->value.vector_double))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_mult(out->value.vector_double, l->value.vector_double, r->value.vector_double, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
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


