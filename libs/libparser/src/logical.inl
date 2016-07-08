#include <stdlib.h>
#include <stdio.h>
#include "../node.h"
#include "../lpl_errors.h"
#include "../debug.h"
lpl_error_code eval_vivi_eq(col_uint * output, const col_int * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  int rsvalue;

  int lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue == rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue == ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] == rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] == r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_eq(col_uint * output, const col_int * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  double rsvalue;

  int lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue == rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue == ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] == rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] == r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_eq(col_uint * output, const col_double * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  int rsvalue;

  double lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue == rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue == ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] == rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] == r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_eq(col_uint * output, const col_double * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  double rsvalue;

  double lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue == rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue == ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] == rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] == r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivi_gt(col_uint * output, const col_int * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  int rsvalue;

  int lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue > rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue > ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] > rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] > r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_gt(col_uint * output, const col_int * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  double rsvalue;

  int lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue > rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue > ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] > rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] > r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_gt(col_uint * output, const col_double * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  int rsvalue;

  double lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue > rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue > ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] > rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] > r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_gt(col_uint * output, const col_double * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  double rsvalue;

  double lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue > rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue > ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] > rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] > r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivi_lt(col_uint * output, const col_int * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  int rsvalue;

  int lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue < rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue < ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] < rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] < r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_lt(col_uint * output, const col_int * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  double rsvalue;

  int lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue < rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue < ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] < rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] < r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_lt(col_uint * output, const col_double * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  int rsvalue;

  double lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue < rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue < ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] < rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] < r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_lt(col_uint * output, const col_double * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  double rsvalue;

  double lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue < rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue < ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] < rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] < r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivi_gteq(col_uint * output, const col_int * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  int rsvalue;

  int lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue >= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue >= ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] >= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] >= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_gteq(col_uint * output, const col_int * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  double rsvalue;

  int lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue >= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue >= ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] >= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] >= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_gteq(col_uint * output, const col_double * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  int rsvalue;

  double lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue >= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue >= ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] >= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] >= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_gteq(col_uint * output, const col_double * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  double rsvalue;

  double lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue >= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue >= ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] >= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] >= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivi_lteq(col_uint * output, const col_int * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  int rsvalue;

  int lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue <= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue <= ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] <= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] <= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vivd_lteq(col_uint * output, const col_int * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  int lsvalue;
  double rsvalue;

  int lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_int_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_int_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue <= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_int_get((col_int*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue <= ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_int*)lng)->d[i] <= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] <= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvi_lteq(col_uint * output, const col_double * l, const col_int * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  int rsvalue;

  double lvalue;
  int rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_int_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_int_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue <= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue <= ((col_int*)lng)->d[i];
      }
    }
    else{
      col_int_get((col_int*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] <= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] <= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
lpl_error_code eval_vdvd_lteq(col_uint * output, const col_double * l, const col_double * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  double lsvalue;
  double rsvalue;

  double lvalue;
  double rvalue;
  unsigned int i;
  col_error e;

  col_double_length(l,&llength);
  col_double_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_double_get(l,0,&lvalue); 
      col_double_get(r,0,&rvalue); 
      return col_uint_set(output,0,lvalue <= rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    if (rlength>llength) { 
      lng = r; 
    } else {
      lng = l;
    }

    if (rlength>llength) {  
      shrt = l;
    } else {
      shrt = r;
    }

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_double_get((col_double*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue <= ((col_double*)lng)->d[i];
      }
    }
    else{
      col_double_get((col_double*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=((col_double*)lng)->d[i] <= rsvalue;
      }
    }

    col_uint__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_uint__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] <= r->d[i];
    }
    col_uint__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
