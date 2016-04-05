#include <stdlib.h>
#include "node.h"
#include "lpl_errors.h"

[@includes]
[@optype_include]

[@start_block]
node* eval_[@op]_node(const node* l, const node* r, Trie *scope){
  node *out;
  int result;
  col_error e;
  lpl_error eval_error;
  if( lpl_is_error_node(l)) {out = _copy_error(l); return out;}
  if( lpl_is_error_node(r)) {out = _copy_error(r); return out;}


  if(LPL_NO_ERROR != (result=lpl_expand_node(l,&l,scope))){
    lpl_make_error_node(out,result,NULL);
    return out;
  }
  if(LPL_NO_ERROR != (result=lpl_expand_node(r,&r,scope))){
    lpl_make_error_node(out,result,NULL);
    return out;
  }

  [@switch_statement]

  return(out);
}
[@end_block]
