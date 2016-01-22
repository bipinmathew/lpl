#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "debug.h"

int main() {
    FILE *fp;
    char commandLine[1024];
    node *result;


    while (fgets(commandLine,1024,stdin)) {
      fp = fopen("errors.log","w");
      ParseTrace(fp,"err: ");

        result=parse(commandLine);

      fclose(fp);
      printNode(result);
      printf("\n");
    }

    return 0;
}
