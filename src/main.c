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
