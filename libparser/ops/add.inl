#include <stdlib.h>
#include <stdio.h>
#include "../node.h"
#include "../lpl_errors.h"
#include "../debug.h"

lpl_error_code eval_vivi_add(col_int * output, const col_int * l, const col_int * r){
  unsigned int llength , rlength,allocate;
  const col_int *shrt, *lng;
  col_error e;
  int svalue, rvalue,output_len;
  unsigned int i;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  dbg("Called col_vivi_add lengths: %d %d\n",llength,rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&svalue); 
      col_int_get(r,0,&rvalue); 
      return col_int_set(output,0,svalue+rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    lng  = (rlength>llength) ? r : l;
    shrt = (rlength>llength) ? l : r;

    if(LIBCOL_NO_ERROR != (e = col_int__realloc(output,&allocate))){
      return e;
    }

    col_int_get(shrt,0,&svalue); 

    for(i=0;i<output_len;i++){
      output->d[i]=svalue+lng->d[i];
    }
    col_int__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_int__realloc(output,&allocate))){
      lpl_make_error_node(output,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i]+r->d[i];
    }
    col_int__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_add(col_double *output, const col_int *l, const col_double *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_add(col_double *output, const col_double *l, const col_int *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_add(col_double *output, const col_double *l, const col_double *r){
  return LPL_NOTIMPLEMENTED_ERROR;
}
