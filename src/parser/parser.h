#ifndef __PARSER_H__
#define __PARSER_H__
#include "nodes/node.h"
#include "lpl_parser.h"
#include "lpl_scanner.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char* tokenInfo, node* result);
void ParseFree(void* parser, void(*freeProc)(void*));
void ParseTrace(FILE *stream, char *zPrefix);

node* parse(const char* commandLine);

#endif
