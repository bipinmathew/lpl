lpl_error_code eval_vivi_[@op](col_[@outtype] * output, const col_[@ltype] * l, const col_[@rtype] * r, lpl_error *eval_error){
  unsigned int llength , rlength,allocate,output_len;
  const void *shrt;
  const void *lng;

  void *svalue;
  [@ltype] lsvalue;
  [@rtype] rsvalue;

  [@ltype] lvalue;
  [@rtype] rvalue;
  unsigned int i;
  col_error e;

  col_[@ltype]_length(l,&llength);
  col_[@rtype]_length(r,&rlength);

  if(rlength==1 || llength==1){
    if(rlength==llength){
      col_[@ltype]_get(l,0,&lvalue); 
      col_[@rtype]_get(r,0,&rvalue); 
      return col_[@outputtype]_set(output,0,lvalue [@opsym] rvalue);
    }

    allocate = output_len = (rlength>llength) ? rlength : llength;

    lng  = (rlength>llength) ? ((col_[@rtype]*)r) : ((col_[@ltype]*)l);
    shrt = (rlength>llength) ? ((col_[@ltype]*)l) : ((col_[@rtype]*)r);

    if(LIBCOL_NO_ERROR != (e = col_[@outputtype]__realloc(output,&allocate))){
      return e;
    }

    if(rlength>llength){
      col_[ltype]_get((col_[@ltype]*)shrt,0,&lsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=lsvalue [@opsym] lng->d[i];
      }
    }
    else{
      col_[rtype]_get((col_[@rtype]*)shrt,0,&rsvalue);
      for(i=0;i<output_len;i++){
        output->d[i]=rsvalue [@opsym] lng->d[i];
      }
    }

    col_[@outtype]__setlength(output,output_len);

    return LPL_NO_ERROR;
  }
  else if(rlength==llength){

    allocate = rlength;

    if(LIBCOL_NO_ERROR != (e = col_[@outputtype]__realloc(output,&allocate))){
      lpl_make_error(&eval_error,LPL_CUSTOM_ERROR,col_error_strings[e]);
      return LPL_CUSTOM_ERROR;
    }

    for(i=0;i<rlength;i++){
      output->d[i]=l->d[i] [@opsym] r->d[i];
    }
    col_[@outputtype]__setlength(output,rlength);

    return LPL_NO_ERROR;
  }
  else{
    return LPL_INVALIDDIMS_ERROR;
  }
  
  return LPL_NOTIMPLEMENTED_ERROR;
}
