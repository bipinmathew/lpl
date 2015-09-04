#include <stdio.h>
#include <stdlib.h>
#define DEBUG_BUILD
#include "node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, Node** result);
void ParseFree(void* parser, void(*freeProc)(void*));
void ParseTrace(FILE *stream, char *zPrefix);

Node* parse(const char* commandLine) {
    /*  Set up the scanner */
    yyscan_t scanner;
    YY_BUFFER_STATE bufferState;
    void* shellParser;
    int lexCode;
    Node *result=NULL;
    // initNode(&result);

    yylex_init(&scanner);

    bufferState = yy_scan_string(commandLine, scanner);

    /*  Set up the parser */
    shellParser = ParseAlloc(malloc);

    do {
        lexCode = yylex(scanner);
        dbg("Token: " << yyget_text(scanner) << std::endl );
        try{
          Parse(shellParser, lexCode, yyget_text(scanner), &result);
        }
        catch(std::exception &e){
          if(result != NULL) delete result;
          yy_delete_buffer(bufferState, scanner);
          yylex_destroy(scanner);
          ParseFree(shellParser, free);
          throw e;
        }

    }
    while (lexCode > 0 );

    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }

    /*  Cleanup the scanner and parser */
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return result;
}


void evalHelper(const Node *root, evalVisitor *v){
  if(root->getLeft()!=NULL)
    evalHelper(root->getLeft(),v);
  if(root->getRight()!=NULL)
    evalHelper(root->getRight(),v);
  root->accept(v);
}

const Node* eval(const Node *root){
	const Node* r;
	evalVisitor *v = new evalVisitor();
  try{
	  evalHelper(root,v);
  }
  catch(std::exception &e){
		std::cerr << e.what() << std::endl;
    v->cleanup();
    delete v;
    throw e;
  }
	r = v->getTop()->clone();
  v->cleanup();
	delete v;
	return r;
}

bool check(const char *str,double _value){
  const Node *root=NULL, *result=NULL;
	bool r=0;
  int retval;
  doubleNode *value;

  printf("Trying: %s\n",str);

	try{
    value = new doubleNode(_value);
    root=parse(str);
		result = eval(root);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
    if (root!=NULL)  delete root;
		delete value;
		return 0;
	}

  r = !((*result)==(*value));
	delete root;
	delete result;
	delete value;
	return r;
}

int main() {
    FILE *fp;
    char commandLine[1024];
    Node *result;

    fp = fopen("errors.log","w");
    ParseTrace(fp,"err: ");

    if(check("1+2",3)){
       printf("FAIL!\n");
    }

    if(check("1+2*3",7)){
      printf("FAIL!\n");
    }

    if(check("1+2*3.0",7)){
       printf("FAIL!\n");
    }

    if(check("(1+2)*(3+4)",21)){
      printf("FAIL!\n");
    }

    if(check("(1*2)+(3*4)",14)){
      printf("FAIL!\n");
    }

    if(check("9+(1+2)/0",10)){
      printf("FAIL!\n");
    } 
    if(check("+++",10)){
      printf("FAIL!");
    }
    if(check("3+++3",6)){
      printf("FAIL!\n");
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
    fclose(fp);
    return 0;
}
