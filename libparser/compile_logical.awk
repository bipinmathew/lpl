function gen_switch_statement(op){
  output=""
  output=ouput "switch(l->type){\n"
    for (ltype in types){
      output=output "  case " types[ltype] "_node:\n"
        output=output "    switch(r->type){\n"
        for (rtype in types){
          output=output "      case " types[rtype] "_node:\n"
            col_type    = (("col_double"==col_types[rtype])||("col_double"==col_types[ltype])||("div"==op)) ? "col_double" : "col_int"
            output_type = "vector_uint"
            output=sprintf("%s        initNode(\\&out,NULL,NULL,%s_node);\n",output,output_type)
            output=sprintf("%s        if(LIBCOL_NO_ERROR!=(e=%s_init(\\&out->value.%s))){lpl_make_error_node(out,e,col_error_strings[e]); return (out);}\n",output,col_type,output_type)
            output=sprintf("%s        if(LPL_NO_ERROR!=eval_%s%s_%s(out->value.%s, l->value.%s, r->value.%s, \\&eval_error)){\n",output,short_types[ltype],short_types[rtype],op,output_type,types[ltype],types[rtype])
              output=output "          lpl_make_error_node(out,eval_error.error_code,eval_error.error_string);\n"
              output=output "        }\n"
          output=output "      break;\n"
        }
        output=output "      default:\n"
        output=output "        lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);\n"
        output=output "      break;\n"
        output=output "    }\n"
      output=output "  break;\n"
    }

  output=output "  default:\n"
  output=output "    lpl_make_error_node(out,LPL_INVALIDARGS_ERROR,NULL);\n"
  output=output "  break;\n"
  output=output "}\n"

  return output
}

function gen_headers(op){
  output = ""
  for(ltype in col_types){
    for(rtype in col_types){
      output_type = "vector_uint"
      output=output sprintf("static lpl_error_code eval_%s%s_%s(%s *output, const %s *  l, const %s *  r, lpl_error *eval_error);\n",short_types[ltype],short_types[rtype],op,output_type,col_types[ltype],col_types[rtype])
    }
  }
  return output
}


BEGIN{
  split("eq gt lt gteq lteq",ops," ")
  split("vector_int vector_double",types," ")
  split("col_int col_double",col_types," ")
  split("vi vd",short_types," ")
  
  FS=""
  header = ""
  output = ""
}

/@includes/ {
  inline_includes = ""
  for(op in ops){
    header = header gen_headers(ops[op])
    inline_includes = inline_includes "#include \"ops/" ops[op] ".inl\"\n"
  }
  #$0=gensub(/@includes/,header,"g",$0)
  print header
  #print inline_includes
  $0=""
}

/@start_block/ {

  getline
 
  block = "" 
  while($0 != "@end_block"){
    block = block $0 "\n"
    $0 = ""
    getline
  } 
  $0 = ""


  output = ""

  for( i in ops) {
    tmp = gensub(/@op/,ops[i],"g",block)
    output = output gensub(/@switch_statement/,gen_switch_statement(ops[i]),"g",tmp)
  }
  print output

}

/.*/ {print $0}


