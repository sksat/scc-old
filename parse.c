#include <stddef.h>
#include "parse.h"

void print_expr(ast_t* expr){
	size_t i;
	if(expr->type == aAssign){
		printf("assign[");
		string_print(expr->token->str);
		printf("]<< ");
	}else printf("expr[%u]<< ", expr->node->size);
	for(i=0;i<expr->node->size;i++){
		ast_t *var = vector_get(expr->node, i);
		printf("[");
		if(var->type == aExpr || var->type == aAssign) print_expr(var);
		else string_print(var->token->str);
		printf("] ");
	}
	printf(">>");
}

void parse_expr_assignment(ast_t *expr){
	size_t i;
	for(i=expr->node->size-1;0<i;i--){
		ast_t *a = vector_get(expr->node, i);
		if(a->type == aUnknown && is_assignment_token(a->token)){
			bool flg = false;
			size_t k;
			expr->token	= a->token;
			ast_t *lval	= ast_new(expr);
			ast_t *rval	= ast_new(expr);
			lval->type = rval->type = aExpr;
			for(k=0;k<i;k++){
				a = vector_get(expr->node, k);
				if(is_assignment_token(a->token)) flg = true;
				vector_push_back(lval->node, a);
			}
			if(flg) parse_expr_assignment(lval);
			for(k=i+1;k<expr->node->size;k++){
				a = vector_get(expr->node, k);
				vector_push_back(rval->node, a);
			}
			expr->type = aAssign;
			expr->node->size = 0;
			vector_push_back(expr->node, lval);
			vector_push_back(expr->node, rval);
		}
	}
}

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
			i = k+1;
		}else{
			ast_t* sub = ast_new(parent);
			switch(tok->type){
				case tDigit:
				case tChar:
					sub->type = aImm;
					break;
				case tOperator:
					sub->type = aUnknown; // temporary
					break;
				case tUnknown:
					sub->type = aVar;
					break;
				default:
					error("unknown token");
					break;
			}
			sub->token= tok;
			vector_push_back(expr->node, sub);
		}
	}

	print_expr(expr);
	printf("\n");

	parse_expr_assignment(expr);
	print_expr(expr);
	printf("\n");

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
