#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trie.h"

#include "parser.h"
#include "debug.h"

int main(void) {
    FILE *fp;
    char commandLine[1024];
    node *result,*eval;
    clock_t start, diff;
    double wtime;
    int msec;


    Trie *scope;
    scope = trie_new();


    struct timespec now, tmstart;


    while (fgets(commandLine,1024,stdin)) {
      commandLine[strcspn(commandLine,"\r\n")]=0;
      if(strlen(commandLine)>0){
#ifdef DEBUG
#if DEBUG
        fp = fopen("errors.log","w");
        ParseTrace(fp,"");
#endif
#endif

        clock_gettime(CLOCK_REALTIME, &tmstart);

          start = clock();
            parse(commandLine,&result);
            eval = evalNode(result,scope);
            if(result->type==ident_node){
              printNode(eval,scope);
            }
            else if(result->type!=assign_node){
              printNode(eval,scope);
            }
            printf("\n");

            releaseNode(result);
            releaseNode(eval);
          diff = clock()-start;

        clock_gettime(CLOCK_REALTIME, &now);

        wtime = 1000*((double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9)));


        msec = diff*1000 / CLOCKS_PER_SEC;

        printf("walltime: %f, cputime: %d ms\n",wtime,msec);
#ifdef DEBUG
#if DEBUG
        fclose(fp);
#endif
#endif
      }
    }

    return 0;
}
