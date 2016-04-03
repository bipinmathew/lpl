#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trie.h"
#include "queue.h"

#include "parser.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    FILE *fp,*sp;
    char commandLine[1024];
    Queue *q;
    node *result, *eval;
    clock_t start, diff;
    double wtime;
    int msec;


    Trie *scope;
    scope = trie_new();


    struct timespec now, tmstart;
    if(argc<=1){
      sp = stdin;
    }
    else{
      dbg("Started execution of file: %s\n",argv[1]);
      if(NULL==(sp = fopen(argv[1],"r"))){
        printf("Failed to open file: %s\n",argv[1]);
      }
    }

    /* If no filename is specified run REPL loop */
#ifdef DEBUG
#if DEBUG
    fp = fopen("errors.log","w");
    ParseTrace(fp,"");
#endif
#endif
    clock_gettime(CLOCK_REALTIME, &tmstart);
    start = clock();
      parseFile(sp,&q);
      fclose(sp);
      while(!queue_is_empty(q)){
        dbg("%s","Processing queue..\n");
        result = queue_pop_head(q);
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
      }
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
  return 0;
}
