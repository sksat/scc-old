#include "util.h"
#include "string.h"

string_t* read_file(FILE *fp){
	int c;
	size_t i = 0;

	long fsize = get_filesize(fp);
	printf("file size: %ld\n", fsize);

	string_t *str = string_new(fsize);

	while(c = fgetc(fp)){
		if(c == EOF) break;
		string_set(str, i, c);
		i++;
	}

	return str;
}

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
