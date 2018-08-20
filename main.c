#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	exit(-1);
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("> %s SRCFILE\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) error("cannot open file: \"%s\"", argv[1]);

	// tokenize
	// parse
	// generate code

	fclose(fp);
}
