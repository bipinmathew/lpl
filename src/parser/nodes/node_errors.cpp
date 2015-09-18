#include "node_errors.h"

const char* divByZeroError::what() const throw(){ return "Divide by Zero."; }
const char* syntaxError::what() const throw(){ return "syntax error."; }
