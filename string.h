#ifndef STRING_H_
#define STRING_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	size_t size;
	char *data;
} string_t;

string_t* string_new(size_t size);
void string_free(string_t *str);

string_t* to_string(const char *s);

void string_set(string_t *str, size_t pos, char c);
char string_get(string_t *str, size_t pos);

bool string_cmp(string_t *s1, string_t *s2);
bool string_match(string_t *str, string_t *s);

void string_print(string_t *str);

#endif
