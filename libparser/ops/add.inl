#include <stdlib.h>
#include <stdio.h>
#include "../node.h"
#include "../lpl_errors.h"
#include "../debug.h"

col_error eval_vivi_add(col_int *output, const col_int *l, const col_int *r){
  unsigned int llength , rlength,allocate;
  int lvalue, rvalue;
  unsigned int i;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  dbg("Called col_vivi_add lengths: %d %d\n",llength,rlength);



  if(rlength==1 || llength==1){
    if(rlength==llength){

      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      col_int_set(output,0,lvalue+rvalue);
      return LPL_NO_ERROR;
    }
    if(rlength>llength){
      col_int_get(l,0,&lvalue); 

      for(i=0;i<rlength;i++){
        col_int_get(r,i,&rvalue);
        col_int_set(output,i,lvalue+rvalue);
      }
    }
    else{
    }
  }
  else if(rlength==llength){

  }
  else{
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
col_error eval_vivd_add(col_double *output, const col_int *l, const col_double *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
col_error eval_vdvi_add(col_double *output, const col_double *l, const col_int *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
col_error eval_vdvd_add(col_double *output, const col_double *l, const col_double *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
