#ifndef __PARSER_H__
#define __PARSER_H__
#include "nodes/node.h"
Node* parse(const char* commandLine);
const terminalNode* eval(const Node *root);

void ParseTrace(FILE *stream, char *zPrefix);
#endif
