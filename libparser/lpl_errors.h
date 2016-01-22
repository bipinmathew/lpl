#ifndef __LPL_ERRORS_H__
#define __LPL_ERRORS_H__
#define LPL_SYNTAX_ERROR 0
#define LPL_DIVBYZERO_ERROR 1
#define LPL_INVALIDARGS_ERROR 2
static const char* lpl_error[] =
{
    "Syntax error.",
    "Divide by zero.",
    "Invalid arguments."
};
#endif
