#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(const char *fmt, ...);

size_t get_filesize(FILE *fp);
