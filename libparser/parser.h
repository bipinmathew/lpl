#ifndef __PARSER_H__
#define __PARSER_H__
#include "node.h"
#include "queue.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, char* tokenInfo, Queue* result);
void ParseFree(void* parser, void(*freeProc)(void*));
void ParseTrace(FILE *stream, char *zPrefix);

int parse(const char* commandLine, Queue** result );

#endif
