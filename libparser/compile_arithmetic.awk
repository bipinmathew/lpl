function gen_switch_statement(op){
  output=""
  output=ouput "switch(l->type){\n"
    for (ltype in types){
      output=output "  case " types[ltype] ":\n"
        output=output "    switch(r->type){\n"
        for (rtype in types){
          output=output "      case " types[rtype] ":\n"
            output=sprintf("%s        eval_%s%s_%s(\\&out,l,r);\n",output,short_types[ltype],short_types[rtype],op)
          output=output "      break;\n"
        }
        output=output "      default:\n"
        output=output "        _error(\\&out,LPL_INVALIDARGS_ERROR);\n"
        output=output "      break;\n"
        output=output "    }\n"
      output=output "  break;\n"
    }

  output=output "  default:\n"
  output=output "    _error(\\&out,LPL_INVALIDARGS_ERROR);\n"
  output=output "  break;\n"
  output=output "}\n"

  return output
}

function gen_headers(op){
  output = ""
  for(ltype in types){
    for(rtype in types){
      output=output sprintf("static col_error eval_%s%s_%s(node **output, const node *l, const node *r);\n",short_types[ltype],short_types[rtype],op)
    }
  }
  return output
}


BEGIN{
  split("add sub mult div",ops," ")
  split("vector_int_node vector_double_node",types," ")
  split("vi vd",short_types," ")
  
  FS=""
  header = ""
  output = ""
}

/@includes/ {
  for(op in ops){
    header = header gen_headers(ops[op])
  }
  #$0=gensub(/@includes/,header,"g",$0)
  print header
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


