#include <stdlib.h>
#include "node.h"
#include "lpl_errors.h"

@includes

@start_block
node* eval_@op_node(const node* l, const node* r, Trie *scope){
  TrieValue  sym_val;
  node *out;
  int result;
  col_error e;
  if( _has_error(l)) {out = _copy_error(l); return out;}
  if( _has_error(r)) {out = _copy_error(r); return out;}

  initNode(&out, NULL, NULL, scalar_null_node);

  if(result=_expand_node(l,&l,scope)){
    _error(&out,result);
    return out;
  }
  if(result=_expand_node(r,&r,scope)){
    _error(&out,result);
    return out;
  }

  @switch_statement

  return(out);
}
@end_block
