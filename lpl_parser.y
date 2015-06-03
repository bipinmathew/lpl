%include
{
  #include <stdio.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <iostream>
}

%syntax_error
{
  *valid = false;
}

%token_type {const char*}
%extra_argument {bool* valid}

start ::= expr .
expr ::= NUMBER(B) PLUS NUMBER(C) .   { int ans=0; ans =atoi(B)+atoi(C); printf("Doing an addition %d+%d=%d\n",atoi(B),atoi(C),ans); }
