#include <stddef.h>
#include "ast.h"

ast_t* ast_new(){
	ast_t* ret = (ast_t*)malloc(sizeof(ast_t));
	ret->node = vector_new(0);
	return ret;
}

void ast_free(ast_t* ast){
	vector_free(ast->node);
	free(ast);
}

void ast_print_impl(size_t indent, ast_t* ast){
	switch(ast->type){
		case aGlobal:
		case aBlock:
			print_indent(indent);
			puts("{");
			{
				size_t i;
				for(i=0;i<ast->node->size;i++){
					ast_t* sub = vector_get(ast->node, i);
					ast_print_impl(indent+4, sub);
				}
			}
			print_indent(indent);
			puts("}");
			break;
		case aDefVar:
			print_indent(indent);
			printf("def-var(");
			printf("size: %u", ast->node->size);
			{
				token_t* t_type = vector_get(ast->node, 0);
				token_t* t_name = vector_get(ast->node, 1);
				printf(", type: ");
				string_print(t_type->str);
				printf(", name: ");
				string_print(t_name->str);
			}

			printf(")\n");
			break;
		default:
			print_indent(indent);
			printf("unknown\n");
			break;
	}
}

void ast_print(ast_t* ast){
	ast_print_impl(0, ast);
}
