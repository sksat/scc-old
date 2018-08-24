#include "token.h"
#include "vector.h"

vector_t *types;
vector_t *delimiters;

token_t space_token;

char* default_types[2] = {
	"char",
	"int",
};

char* delimiter_str[40] = {
	"(", ")",
	"{", "}",
	"[", "]",
	",", "?", ":", ";",
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
	"^=", "^"
};

void init_token(){
	types = vector_new(0);
	delimiters = vector_new(0);

	size_t i;
	for(i=0; i<2; i++){
		vector_push_back(types, to_string(default_types[i]));
	}
	for(i=0; i<40; i++){
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

	tok = (token_t*)malloc(sizeof(token_t));
	tok->str = NULL;

	char c = string_get(src, 0);

	// comment
	if(c == '/'){
		char c2 = string_get(src, 1);
		if(c2 == '/'){
			for(i=2;i<src->size;i++){
				if(string_get(src, i) == '\n'){
					tok->str = string_view(src, 0, i);
					tok->type= tComment;
					return tok;
				}
			}
		}else if(c2 == '*'){
			for(i=3;i<src->size;i++){
				if(string_get(src, i-1) == '*' && string_get(src, i) == '/'){
					tok->str = string_view(src, 0, i+1);
					tok->type= tComment;
					return tok;
				}
			}
		}
	}

	switch(c){
		case ' ':
		case '\t':
		case '\n':
			return &space_token;
		default:
			break;
	}

	for(i=0; i<types->size; i++){
		string_t *t = vector_get(types, i);
		if(string_match(src, t)){
			tok->str = t;
			tok->type = tType;
			return tok;
		}
	}
	for(i=0; i<delimiters->size; i++){
		string_t *t = vector_get(delimiters, i);
		if(string_match(src, t)){
			tok->str = t;
			if((tDelim+i) < tOperator)
				tok->type = tDelim + i + 1;
			else tok->type = tOperator;
			return tok;
		}
	}

	for(i=0; i<src->size; i++){
		size_t k;
		c = string_get(src, i);
		for(k=0; k<delimiters->size; k++){
			string_t* d = vector_get(delimiters, k);
			if(c == string_get(d, 0) || c == '\n' || c == '\t' || c == ' '){
				tok->str = string_view(src, 0, i);
				tok->type = tUnknown;
				if(string_is_digit(tok->str)) tok->type = tDigit;
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

bool is_assignment_token(token_t *tok){
	if(tok->type != tOperator) return false;
	if(tok->str->size == 1){
		if(string_get(tok->str, 0) == '=') return true;
		else return false;
	}else if(string_get(tok->str, 1) == '=') return true;
	else return false;
}

/*
9: * / %
8: + -
7: << >>
6: < <= > >=
5: == !=
4: &
3: ^
2: |
1: &&
0: ||
 */
size_t token_get_priority(token_t *tok){
	char c1 = string_get(tok->str, 0);
	if(tok->str->size == 1){
		switch(c1){
			case '*':
			case '/':
			case '%':
				return 9;
			case '+':
			case '-':
				return 8;
			case '&':
				return 4;
			case '^':
				return 3;
			case '|':
				return 2;
		}
	}else return 0;
}

const char* token_type2name(int type){
	switch(type){
		case tComment:	return "comment";
		case tType:		return "type";
		case tDigit:	return "digit";
		case tString:	return "string";
		case tChar:		return "char";
		case tDelim:	return "delim";
		case tOperator:	return "op";
		default:
			if(tDelim < type && type < tOperator)
				return delimiter_str[type - tDelim -1];
			return "ident";
	}
}
