#ifndef AST_H_
#define AST_H_

#include "vector.h"
#include "token.h"

typedef enum {
	aDefVar,
	aExpr,
} ASTType;

typedef struct {
	vector_t *node;
} ast_t;

ast_t* ast_new();

#endif
