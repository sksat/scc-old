#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "string.h"

void error(const char *fmt, ...);

size_t get_filesize(FILE *fp);
string_t* read_file(FILE *fp);
