#include "util.h"
#include "string.h"
#include "vector.h"
#include "token.h"
#include "parse.h"

int main(int argc, char **argv){
	if(argc != 2){
		printf("> %s SRCFILE\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) error("cannot open file: \"%s\"", argv[1]);

	string_t *all_src = read_file(fp);
	string_t *src = all_src;

	string_print(src);

	// tokenize
	init_token();
	vector_t *token_list = vector_new(0);
	while(true){
		token_t *tok = get_token(src);
		if(tok == NULL) break;
		string_slide(src, tok->str->size);
		if(tok == &space_token) continue;
		if(tok->type == tComment) continue;
		vector_push_back(token_list, tok);
	}

	printf("token list:\n");
	for(size_t i=0; i<token_list->size; i++){
		token_t *t = vector_get(token_list, i);
		printf("%s:\t\"", token_type2name(t->type));
		string_print(t->str);
		printf("\"\n");
	}

	// parse
	ast_t* ast = parse(token_list);
	ast_print(ast);

	// generate code

	//string_free(all_src);
	vector_free(token_list);
	fclose(fp);
}
