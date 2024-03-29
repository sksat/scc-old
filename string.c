#include <string.h>
#include "string.h"
#include "util.h"

string_t* string_new(size_t size){
	string_t *str = (string_t*)malloc(sizeof(string_t));
	str->size = size;
	str->data = (char*)malloc(size);
	if(str->data == NULL) error("malloc failed: size=%u", size);
	return str;
}

string_t* string_view(string_t* origin, size_t start, size_t size){
	string_t* str = (string_t*)malloc(sizeof(string_t));
	str->size = size;
	str->data = origin->data + start;
	return str;
}

void string_free(string_t *str){
	free(str->data);
	free(str);
}

void string_slide(string_t *str, size_t i){
	if(str->size < i) error("slide failed");
	str->data += i;
	str->size -= i;
}

string_t* to_string(const char *s){
	string_t *str = string_new(strlen(s));
	str->data = (void*)s;
	return str;
}

void string_set(string_t *str, size_t pos, char c){
	str->data[pos] = c;
}

char string_get(string_t *str, size_t pos){
	if(str->size <= pos) error("string_t size error");
	return str->data[pos];
}

bool string_cmp(string_t *s1, string_t *s2){
	size_t i;
	if(s1->size != s2->size) return false;
	for(i=0; i<s1->size; i++){
		if(s1->data[i] != s2->data[i]) return false;
	}
	return true;
}

bool string_match(string_t *str, string_t *s){
	size_t i;
	if(str->size < s->size) return false;
	for(i=0; i<s->size; i++){
		if(str->data[i] != s->data[i]) return false;
	}
	return true;
}

bool string_is_digit(string_t *str){
	size_t i;
	for(i=0; i<str->size; i++){
		if(str->data[i] < '0' || '9' < str->data[i]) return false;
	}
	return true;
}

void string_print(string_t *str){
	size_t i;
	for(i=0; i<str->size; i++){
		putchar(str->data[i]);
	}
}
