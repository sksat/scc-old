#include "util.h"
#include "string.h"

int main(int argc, char **argv){
	if(argc != 2){
		printf("> %s SRCFILE\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) error("cannot open file: \"%s\"", argv[1]);

	string_t *src = read_file(fp);

	string_print(src);

	// tokenize
	// parse
	// generate code

	string_free(src);
	fclose(fp);
}
