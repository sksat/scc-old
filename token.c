#include "token.h"
#include "vector.h"

vector_t *types;
vector_t *delimiters;

token_t space_token;

void init_token(){
	static char* default_types[2] = {
		"char",
		"int",
	};
	static char* delimiter_str[37] = {
		"(", ")",
		"{", "}",
		"[", "]",
		"&&", "&=", "&",
		"||", "|=", "|",
		"<<", "<=", "<",
		">=", ">",
		"--", "-=", "->", "-",
		"++", "+=", "+",
		"*=", "*",
		"/=", "/",
		"==", "=",
		"!=", "!",
		"%=", "%",
		",", "?", "^",
	};

	types = vector_new(0);
	delimiters = vector_new(0);

	size_t i;
	for(i=0; i<2; i++){
		vector_push_back(types, to_string(default_types[i]));
	}
	for(i=0; i<37; i++){
		vector_push_back(delimiters, to_string(delimiter_str[i]));
	}

	printf("default type list:\n");
	for(i=0;i<types->size;i++){
		printf("\t");
		string_print(vector_get(types, i));
		printf("\n");
	}

	space_token.str = to_string(" ");
}

token_t* get_token(string_t *src){
	size_t i;
	token_t* tok;
	static token_t* next_token;

	if(src->size == 0) return NULL;

	char c = string_get(src, 0);
	switch(c){
		case ' ':
		case '\t':
		case '\n':
			return &space_token;
		default:
			break;
	}

	tok = (token_t*)malloc(sizeof(token_t));
	tok->str = NULL;

	for(i=0; i<types->size; i++){
		string_t *t = vector_get(types, i);
		if(string_match(src, t)){
			tok->str = t;
			return tok;
		}
	}
	for(i=0; i<delimiters->size; i++){
		string_t *t = vector_get(delimiters, i);
		if(string_match(src, t)){
			tok->str = t;
			return tok;
		}
	}

	for(i=0; i<src->size; i++){
		size_t k;
		c = string_get(src, i);
		for(k=0; k<delimiters->size; k++){
			string_t* d = vector_get(delimiters, k);
			if(c == string_get(d, 0) || c == '\n' || c == '\t' || c == ' '){
				tok->str = (string_t*)malloc(sizeof(string_t));
				tok->str->data = src->data;
				tok->str->size = i;
				return tok;
			}
		}
	}

	if(tok->str == NULL){
		free(tok);
		return NULL;
	}
	return tok;
}
