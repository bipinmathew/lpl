#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "nodes/debug.h"

node* parse(const char* commandLine) {
    /*  Set up the scanner */

    dbg("Parsing: %s \n",commandLine);
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
    while ( lexCode > 0 );

    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }

    /*  Cleanup the scanner and parser */
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return result;
}


