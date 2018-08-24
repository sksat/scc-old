#ifndef AST_H_
#define AST_H_

#include "vector.h"
#include "token.h"

typedef enum {
	aUnknown,
	aGlobal,
	aBlock,
	aDefVar,
	aExpr,
	aAssign,
	aVar,
	aImm,
} ASTType;

typedef struct ast_t ast_t;

typedef struct ast_t {
	int type;
	ast_t *parent;
	token_t *token;
	vector_t *node;
} ast_t;

ast_t* ast_new(ast_t* parent);
void ast_free(ast_t* ast);

void ast_print(ast_t* ast);

#endif
