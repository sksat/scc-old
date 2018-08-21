#include <stddef.h>
#include "parse.h"

ast_t* parse(vector_t *token_list){
	ast_t *global = ast_new();
	token_t *tok;

	global->type = aGlobal;
	tok = vector_get(token_list, 0);
	switch(tok->type){
		case tType:
			{
				ast_t* defvar = ast_new();
				defvar->type  = aDefVar;
				vector_push_back(defvar->node, tok); // 型
				vector_push_back(defvar->node, vector_get(token_list, 1)); // 変数名
				vector_push_back(global->node, defvar);
			}
			break;
		default:
			break;
	}

	return global;
}
