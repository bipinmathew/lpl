#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "debug.h"

int main() {
    FILE *fp;
    char commandLine[1024];
    node *result;
    clock_t start, diff;
    int msec;


    while (fgets(commandLine,1024,stdin)) {
#ifdef DEBUG
      fp = fopen("errors.log","w");
      ParseTrace(fp,"err: ");
#endif
      start = clock();
      result=parse(commandLine);
      diff = clock()-start;
      msec = diff*1000 / CLOCKS_PER_SEC;

      printNode(result);
      printf("\n");
      printf("%s, cputime: %d ms\n",commandLine,msec);
#ifdef DEBUG
      fclose(fp);
#endif
    }

    return 0;
}
