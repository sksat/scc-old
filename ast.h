#ifndef AST_H_
#define AST_H_

#include "vector.h"
#include "token.h"

typedef enum {
	aGlobal,
	aBlock,
	aDefVar,
	aExpr,
} ASTType;

typedef struct {
	int type;
	vector_t *node;
} ast_t;

ast_t* ast_new();
void ast_free(ast_t* ast);

void ast_print(ast_t* ast);

#endif
