#include "util.h"
#include "string.h"
#include "token.h"

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

	init_token();
	while(true){
		token_t *tok = get_token(src);
		if(tok == NULL) break;
		string_slide(src, tok->str->size);
		printf("\"");
		string_print(tok->str);
		printf("\"\n");
	}

	// tokenize
	// parse
	// generate code

	//string_free(all_src);
	fclose(fp);
}
