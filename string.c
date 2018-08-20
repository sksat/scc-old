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

void string_print(string_t *str){
	size_t i;
	for(i=0; i<str->size; i++){
		putchar(str->data[i]);
	}
}
