#!/bin/bash

OP=("eq" "gt" "lt" "gteq" "lteq")
OPSYM=("==" ">" "<" ">=" "<=")
TYPE=("int" "double")



echo '#include <stdlib.h>
#include <stdio.h>
#include "../node.h"
#include "../lpl_errors.h"
#include "../debug.h"' 



for (( I=0 ; $I < ${#OP[@]} ; I+=1)); do
  op="${OP[$I]}"
  sym="${OPSYM[$I]}"

  for ltype in "${TYPE[@]}"
  do
    for rtype in "${TYPE[@]}"
    do
      outputtype="uint"

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

      sed "s/\[@op\]/$op/g ; s/\[@opsym\]/$sym/g; s/\[@ltype\]/$ltype/g ; s/\[@rtype\]/$rtype/g ; s/\[@outtype\]/$outputtype/g ; s/\[@lshort\]/$lshort/g ; s/\[@rshort\]/$rshort/g" $1 
    done
  done
done
