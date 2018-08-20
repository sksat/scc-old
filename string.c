#include "string.h"
#include "util.h"

string_t* string_new(size_t size){
	string_t *str = (string_t*)malloc(sizeof(string_t));
	str->size = size;
	str->data = (char*)malloc(size);
	if(str->data == NULL) error("malloc failed: size=%u", size);
	return str;
}

void string_free(string_t *str){
	free(str->data);
	free(str);
}

void string_set(string_t *str, size_t pos, char c){
	str->data[pos] = c;
}

char string_get(string_t *str, size_t pos){
	if(str->size > pos) error("string_t size error");
	return str->data[pos];
}

void string_print(string_t *str){
	size_t i;
	for(i=0; i<str->size; i++){
		putchar(str->data[i]);
	}
}
