#include <stdlib.h>

typedef struct {
	size_t size;
	char *data;
} string_t;

string_t* string_new(size_t size);
void string_free(string_t *str);

void string_set(string_t *str, size_t pos, char c);
char string_get(string_t *str, size_t pos);
void string_print(string_t *str);
