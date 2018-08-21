#include "util.h"

void error(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	exit(-1);
}

size_t get_filesize(FILE *fp){
	fseek(fp, 0L, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	return size;
}

string_t* read_file(FILE *fp){
	int c;
	size_t i = 0;

	size_t fsize = get_filesize(fp);

	string_t *str = string_new(fsize);

	while(c = fgetc(fp)){
		if(c == EOF) break;
		string_set(str, i, c);
		i++;
	}

	return str;
}

void print_indent(size_t indent){
	size_t i;
	for(i=0;i<indent;i++) putchar(' ');
}
