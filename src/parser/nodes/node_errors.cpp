#include "node_errors.h"

const char* divByZeroError::what() const throw(){ return "Divide by Zero."; }
const char* syntaxError::what() const throw(){ return "syntax error."; }
const char* cloneError::what() const throw(){ return "node type cannot be cloned error."; }
const char* unexpectedNumArgsError::what() const throw(){ return "syntax error."; }

