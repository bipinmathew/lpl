#!/bin/bash

OP=("add" "mult" "sub" "div")
#OP=("add")
OPSYM=("+" "*" "-" "\/")
TYPE=("int" "double")



for (( I=0 ; $I < ${#OP[@]} ; I+=1)); do
  op="${OP[$I]}"
  sym="${OPSYM[$I]}"

  for ltype in "${TYPE[@]}"
  do
    for rtype in "${TYPE[@]}"
    do
      if [[("$ltype" = "double") || ("$rtype" = "double") || ("$op" = "div")  ]]; then
        outputtype="double"
      else
        outputtype="int"
      fi

      if [[("$ltype" = "int")]]; then
        lshort="vi"
      else
        lshort="vd"
      fi


      if [[("$rtype" = "int")]]; then
        rshort="vi"
      else
        rshort="vd"
      fi

      sed "s/\[@op\]/$op/g ; s/\[@opsym\]/$sym/g; s/\[@ltype\]/$ltype/g ; s/\[@rtype\]/$rtype/g ; s/\[@outtype\]/$outputtype/g ; s/\[@lshort\]/$lshort/g ; s/\[@rshort\]/$rshort/g" ops.tpl >> ops.inl
    done
  done
done
