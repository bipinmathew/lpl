#include <stdlib.h>
#include "node.h"
#include "lpl_errors.h"

static lpl_error_code eval_vivi_gteq(col_uint *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_gteq(col_uint *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_gteq(col_uint *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_gteq(col_uint *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_lteq(col_uint *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_lteq(col_uint *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_lteq(col_uint *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_lteq(col_uint *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_eq(col_uint *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_eq(col_uint *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_eq(col_uint *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_eq(col_uint *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_gt(col_uint *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_gt(col_uint *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_gt(col_uint *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_gt(col_uint *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vivi_lt(col_uint *output, const col_int *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vivd_lt(col_uint *output, const col_int *  l, const col_double *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvi_lt(col_uint *output, const col_double *  l, const col_int *  r, lpl_error *eval_error);
static lpl_error_code eval_vdvd_lt(col_uint *output, const col_double *  l, const col_double *  r, lpl_error *eval_error);


#include "logical.inl"

node* eval_gteq_node(const node* l, const node* r, Trie *scope){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_gteq(out->value.vector_uint, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_gteq(out->value.vector_uint, l->value.vector_int, r->value.vector_double, &eval_error)){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_gteq(out->value.vector_uint, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_gteq(out->value.vector_uint, l->value.vector_double, r->value.vector_double, &eval_error)){
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
node* eval_lteq_node(const node* l, const node* r, Trie *scope){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_lteq(out->value.vector_uint, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_lteq(out->value.vector_uint, l->value.vector_int, r->value.vector_double, &eval_error)){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_lteq(out->value.vector_uint, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_lteq(out->value.vector_uint, l->value.vector_double, r->value.vector_double, &eval_error)){
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
node* eval_eq_node(const node* l, const node* r, Trie *scope){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_eq(out->value.vector_uint, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_eq(out->value.vector_uint, l->value.vector_int, r->value.vector_double, &eval_error)){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_eq(out->value.vector_uint, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_eq(out->value.vector_uint, l->value.vector_double, r->value.vector_double, &eval_error)){
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
node* eval_gt_node(const node* l, const node* r, Trie *scope){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_gt(out->value.vector_uint, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_gt(out->value.vector_uint, l->value.vector_int, r->value.vector_double, &eval_error)){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_gt(out->value.vector_uint, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_gt(out->value.vector_uint, l->value.vector_double, r->value.vector_double, &eval_error)){
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
node* eval_lt_node(const node* l, const node* r, Trie *scope){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivi_lt(out->value.vector_uint, l->value.vector_int, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vivd_lt(out->value.vector_uint, l->value.vector_int, r->value.vector_double, &eval_error)){
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
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvi_lt(out->value.vector_uint, l->value.vector_double, r->value.vector_int, &eval_error)){
          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);
        }
      break;
      case vector_double_node:
        initDyadicNode(&out,NULL,NULL,vector_uint_node);
        if(LIBCOL_NO_ERROR!=(e=col_uint_init(&out->value.vector_uint))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}
        if(LPL_NO_ERROR!=eval_vdvd_lt(out->value.vector_uint, l->value.vector_double, r->value.vector_double, &eval_error)){
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


