#include <stdio.h>
#include <stdlib.h>
#include "lpl_parser.h"
#include "lpl_scanner.h"
 
void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, int* valid);
void ParseFree(void* parser, void(*freeProc)(void*));
 
void parse(const char* commandLine) {
    // Set up the scanner
    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE bufferState = yy_scan_string(commandLine, scanner);
 
    // Set up the parser
    void* shellParser = ParseAlloc(malloc);
 
    int lexCode;
    int validParse = 1;
    do {
        lexCode = yylex(scanner);
        Parse(shellParser, lexCode, yyget_text(scanner), &validParse);
    }
    while (lexCode > 0 && validParse);
 
    if (-1 == lexCode) {
        fprintf(stderr,"The scanner encountered an error.\n");
    }

    if (!validParse) {
        fprintf(stderr,"The parser encountered an error.\n");
    }
 
    // Cleanup the scanner and parser
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
}
 
int main() {
    char commandLine[1024];
    // while (scanf("%s",commandLine)) {
        // parse(commandLine);
        parse("1+2");
        parse("3+4.0");
        parse("5.0+6");
        parse("6.0+7.0");
    // }
    return 0;
}
