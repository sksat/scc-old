#include <stddef.h>
#include "parse.h"

size_t parse_block(ast_t* parent, vector_t* token_list, size_t i){
	ast_t* ast;
	token_t* tok = vector_get(token_list, i);
	switch(tok->type){
		case tBlockStart:
			error("not implemented: child block.\n");
			break;
		case tBlockEnd:
			return 0;
		case tType: // 変数宣言
			ast = ast_new();
			ast->type = aDefVar;
			vector_push_back(ast->node, tok);		// 型
			tok = vector_get(token_list, i+1);	// 変数名
			vector_push_back(ast->node, tok);
			tok = vector_get(token_list, i+2);	// ; or =
			if(tok->type == tSemicolon){}
			else if(tok->type == tOperator){

			}

			vector_push_back(parent->node, ast);
			return 2;
		default:
			printf("unknown token: ");
			string_print(tok->str);
			printf("\n");
			return 0;
	}
}

ast_t* parse(vector_t *token_list){
	ast_t *global = ast_new();
	global->type = aGlobal;

//	parse_impl(global, token_list);

	size_t i;
	for(i=0; i<token_list->size; i++){
		i += parse_block(global, token_list, i);
	}

	return global;
}
