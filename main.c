#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, node* result);
void ParseFree(void* parser, void(*freeProc)(void*));

node* parse(const char* commandLine) {
    /*  Set up the scanner */
    yyscan_t scanner;
    YY_BUFFER_STATE bufferState;
    void* shellParser;
    int lexCode;
    node *result;
    initNode(&result);

    yylex_init(&scanner);

    bufferState = yy_scan_string(commandLine, scanner);

    /*  Set up the parser */
    shellParser = ParseAlloc(malloc);

    do {
        lexCode = yylex(scanner);
        Parse(shellParser, lexCode, yyget_text(scanner), result);
    }
    while (lexCode > 0 && result->type!=terror);

    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }

    /*  Cleanup the scanner and parser */
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return result;
}

int check(const char *str,double value){
  node *result;
  int retval;

  result=parse(str);

  switch(result->type){
    case tint:
      retval=value!=result->value.i;
    break;
    case tdouble:
      retval=value!=result->value.d;
    break;
    default:
      retval=1;
    break;

  }
  if(retval){
    printf("Test failed on expression: %s \n",str);
  }

  printf(" = ");
  printNode(result);
  printf("\n");

  freeNode(result);
  return retval;
}

int main() {
    FILE *fp;
    char commandLine[1024];
    node *result;

    fp = fopen("errors.log","w");
    ParseTrace(fp,"err: ");

    if(check("1+2*3",7)){
      printf("FAIL!\n");
      exit(1);
    }

    if(check("(1+2)*3+9.0",18)){
      printf("FAIL!\n");
      exit(1);
    }
/*    while (scanf("%s",commandLine)) {
      result=parse(commandLine);
      printNode(result);
      printf("\n");
    } */

/*  check("1+2",3);
  check("1+2+3",6);
  check("3+4.0",7);
  check("5.0+6",11);

  check("1-2",-1);
  check("1-2-3",-4);
  check("3-4.0",-1);
  check("5.0-6",-1);

  check("1*2",2);
  check("1*2*3",6);
  check("3*4.0",12);
  check("5.0*6",30);


  check("1/2",0.5);
  check("3/4.0",0.75);
  check("5.0/6",5.0/6); */

/*  } */
    return 0;
}
