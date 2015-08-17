#include <stdio.h>
#include <stdlib.h>
#define DEBUG_BUILD
#include "node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, Node** result);
void ParseFree(void* parser, void(*freeProc)(void*));

Node* parse(const char* commandLine) {
    /*  Set up the scanner */
    yyscan_t scanner;
    YY_BUFFER_STATE bufferState;
    void* shellParser;
    int lexCode;
    Node *result;
    // initNode(&result);

    yylex_init(&scanner);

    bufferState = yy_scan_string(commandLine, scanner);

    /*  Set up the parser */
    shellParser = ParseAlloc(malloc);

    do {
        lexCode = yylex(scanner);
        Parse(shellParser, lexCode, yyget_text(scanner), &result);
    }
    while (lexCode > 0 );

    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }
    std::cout<<"FLOP"<<std::endl;
    result->identify();

    /*  Cleanup the scanner and parser */
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return result;
}

int check(const char *str,double _value){
  Node *result;
  doubleNode *value = new doubleNode(_value);
  int retval;
  printf("Trying: %s\n",str);

  result=parse(str);
  result->identify();
  // return result==value;
}

int main() {
    FILE *fp;
    char commandLine[1024];
    Node *result;

    // fp = fopen("errors.log","w");
    // ParseTrace(fp,"err: ");

    if(check("1+2",3)){
      printf("FAIL!\n");
    }

//    if(check("1+2*3",7)){
//      printf("FAIL!\n");
//    }

//    if(check("1+2*3.0",7)){
//      printf("FAIL!\n");
//    }

//    if(check("(1+2)*(3+4)",21)){
//      printf("FAIL!\n");
//    }

//    if(check("(1*2)+(3*4)",14)){
//      printf("FAIL!\n");
//    }

//    if(check("9+(1+2)/0",10)){
//      printf("FAIL!\n");
//    }
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
//    fclose(fp);
    return 0;
}
