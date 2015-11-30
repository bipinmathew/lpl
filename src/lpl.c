#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main() {
    FILE *fp;
    char commandLine[1024];
    node *result;

    fp = fopen("errors.log","w");
    ParseTrace(fp,"err: ");

    while (scanf("%s",commandLine)) {
      result=parse(commandLine);
      printNode(result);
      printf("\n");
    }

    fclose(fp);
    return 0;
}
