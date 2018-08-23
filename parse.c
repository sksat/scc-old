#include <stddef.h>
#include "parse.h"

void parse_expr_impl(ast_t* parent, vector_t* token_list, size_t start, size_t end){
	ast_t* expr = ast_new(parent);
	expr->type = aExpr;
	token_t* tok;
	size_t i;
	for(i=start;i<=end;i++){
		tok = vector_get(token_list, i);
		if(tok->type == tBracketStart){
			size_t k;
			for(k=i;k<=end;k++){
				tok = vector_get(token_list, k);
				if(tok->type == tBracketEnd) break;
			}
			parse_expr_impl(expr, token_list, i+1, k-1);
			i = k;
		}else{
			ast_t* sub = ast_new(parent);
			sub->type = aVar;
			sub->token= tok;
			vector_push_back(expr->node, sub);
		}
	}
	vector_push_back(parent->node, expr);
}

size_t parse_expr(ast_t* parent, vector_t* token_list, size_t start){
	token_t* tok;
	size_t read = 0;
	size_t i;
	for(i=start;i<token_list->size;i++){
		tok = vector_get(token_list, i);
		read++;
		if(tok->type == tSemicolon) break;
	}

	parse_expr_impl(parent, token_list, start, i-1);

	return read;
}

size_t parse_block(ast_t* parent, vector_t* token_list, size_t i){
	ast_t *ast, *expr;
	token_t* tok = vector_get(token_list, i);
	size_t read = 0;
	switch(tok->type){
		case tBlockStart:
			error("not implemented: child block.\n");
			break;
		case tBlockEnd:
			return 0;
		case tType: // 変数宣言
			// node[0]: 型
			// node[1]: 変数名
			// node[2]: 式のAST
			ast = ast_new(parent);
			ast->type = aDefVar;
			vector_push_back(ast->node, tok);			// 型
			tok = vector_get(token_list, i+1); read++;	// 変数名
			vector_push_back(ast->node, tok);
			tok = vector_get(token_list, i+2); read++;	// ; or =
			if(tok->type != tSemicolon){
				if(!string_cmp(tok->str, to_string("="))) error("expected \'=\'\n");
				read += parse_expr(ast, token_list, i+3);
			}
			vector_push_back(parent->node, ast);
			return read;
		case tUnknown:
		case tDigit:
			return parse_expr(parent, token_list, i) - 1;
		default:
			printf("unknown token: ");
			string_print(tok->str);
			printf("\n");
			return 0;
	}
}

ast_t* parse(vector_t *token_list){
	ast_t *global = ast_new(NULL);
	global->type = aGlobal;

	size_t i;
	for(i=0; i<token_list->size; i++){
		i += parse_block(global, token_list, i);
	}

	return global;
}
