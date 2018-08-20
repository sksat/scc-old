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
