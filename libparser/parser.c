#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "debug.h"

int parse(const char* commandLine, node **result) {
    /*  Set up the scanner */

    dbg("Parsing: %s \n",commandLine);
    yyscan_t scanner;
    int tok_len;
    char *tok;
    YY_BUFFER_STATE bufferState;
    void* shellParser;
    int lexCode;

    initNode(result,NULL,NULL,scalar_null_node);

    yylex_init(&scanner);

    bufferState = yy_scan_string(commandLine, scanner);

    /*  Set up the parser */
    shellParser = ParseAlloc(malloc);

    do {

        lexCode = yylex(scanner);
        tok = strndup(yyget_text(scanner),tok_len=yyget_leng(scanner));

        dbg("Got Token: %s Token length: %d, Lex code: %d \n",tok,tok_len,lexCode);

        Parse(shellParser, lexCode, tok, result);

    }
    while ( lexCode > 0 );

    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }

    /*  Cleanup the scanner and parser */
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return 0;
}
