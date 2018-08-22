#include <stddef.h>
#include "parse.h"

void parse_impl(ast_t* parent, vector_t* token_list){
	size_t i;
	ast_t* sub;
	token_t* tok;

	for(i=0; i<token_list->size; i++){
		tok = vector_get(token_list, i);
		switch(tok->type){
			case tType:
				sub = ast_new();
				sub->type = aDefVar;
				vector_push_back(sub->node, tok); // 型
				i++;
				tok = vector_get(token_list, i);
				if(string_get(tok->str, 0) == '*'){
					printf("warning: not implemented def-pointer.\n");
					continue;
				}
				vector_push_back(sub->node, tok); // 変数・関数名
				i++;
				tok = vector_get(token_list, i);
				if(string_get(tok->str, 0) == '('){
					printf("warning: not implemented def-function.\n");
					continue;
				}
				{
					char c = string_get(tok->str, 0);
					if(c != ';' && c!= '=') error("expected \';\' or \'=\'\n");
					else if(c == '='){
						ast_t* expr = ast_new();
						expr->type = aExpr;
						for(i++;i<token_list->size;i++){
							tok = vector_get(token_list, i);
							if(string_get(tok->str, 0) == ';') break;
							vector_push_back(expr->node, tok);
						}
						vector_push_back(sub->node, expr);
					}
				}
				vector_push_back(parent->node, sub);
				break;
			default:
				break;
		}
	}
}

ast_t* parse(vector_t *token_list){
	ast_t *global = ast_new();
	global->type = aGlobal;

	parse_impl(global, token_list);

	return global;
}
