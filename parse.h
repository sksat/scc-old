#ifndef PARSE_H_
#define PARSE_H_

#include "vector.h"
#include "ast.h"

ast_t* parse(vector_t *token_list);

#endif
