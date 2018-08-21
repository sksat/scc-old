#include <stddef.h>
#include "parse.h"

ast_t* parse(vector_t *token_list){
	ast_t *ast = ast_new();
	token_t *tok;
	tok = vector_get(token_list, 0);
	switch(tok->type){
		case tType:
			printf("def-var(name:");
			{
				token_t* t = vector_get(token_list, 1);
				string_print(t->str);
			}
			printf(")\n");
			break;
		default:
			break;
	}
}
