%include
{
  #include <stdio.h>
  #include <stdlib.h>
}



start ::= expr .
expr ::= NUMBER PLUS NUMBER .   { printf("Doing an addition...\n"); }
