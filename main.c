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
  freeNode(result);
  if(retval){
    printf("Test failed on expression: %s \n",str);
  }
  return retval;
}

int main() {
    char commandLine[1024];
/*  while (scanf("%s",commandLine)) { */
/*  parse(commandLine); */
  check("1+2",3);
  check("1+2+3",6);
  check("3+4.0",7);
  check("5.0+6",11);

  check("1-2",-1);
  check("1-2-3",-4);
  check("3-4.0",-1);
  check("5.0-6",-1);


/*  } */
    return 0;
}
