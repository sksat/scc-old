#include <stddef.h>
#include "ast.h"

ast_t* ast_new(){
	ast_t* ret = (ast_t*)malloc(sizeof(ast_t));
	return ret;
}
