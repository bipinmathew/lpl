#include "node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, Node** result);
void ParseFree(void* parser, void(*freeProc)(void*));
void ParseTrace(FILE *stream, const char *zPrefix);

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

		// FILE *fp;
		// fp = fopen("errors.log","w");
		// ParseTrace(fp,"");

    do {
        lexCode = yylex(scanner);
        dbg("Token: " << yyget_text(scanner) << std::endl );
        try{
          Parse(shellParser, lexCode, yyget_text(scanner), &result);
        }
        catch(syntaxError &e){
          if(result != NULL) delete result;
					// ParseTrace(NULL,"");
					// fclose(fp);
          yy_delete_buffer(bufferState, scanner);
          yylex_destroy(scanner);
          ParseFree(shellParser, free);
          throw e;
        }
        catch(std::exception &e){
          if(result != NULL) delete result;
					// ParseTrace(NULL,"");
					// fclose(fp);
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
		// ParseTrace(NULL,"");
		// fclose(fp);
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
    return result;
}


