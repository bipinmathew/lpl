#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, node* result);
void ParseFree(void* parser, void(*freeProc)(void*));

void parse(const char* commandLine, node *result) {
    /*  Set up the scanner */
    yyscan_t scanner;
    YY_BUFFER_STATE bufferState;
    void* shellParser;
    int lexCode;

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
}

int main() {
    char commandLine[1024];
    node *result;
    initNode(&result);
/*  while (scanf("%s",commandLine)) { */
/*  parse(commandLine); */
        parse("1+2",result);
        print(result);
        parse("1+2+3",result);
        print(result);
        parse("3+4.0",result);
        print(result);
        parse("5.0+6",result);
        print(result);
        /* parse("6.0+7.0+a",result);
        print(result); */

        parse("1-2",result);
        print(result);
        parse("1-2-3",result);
        print(result);
        parse("3-4.0",result);
        print(result);
        parse("5.0-6",result);
        print(result);
        /* parse("6.0-7.0-a",result); 
        print(result); */

        freeNode(result);

/*  } */
    return 0;
}
