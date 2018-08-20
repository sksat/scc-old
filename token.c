#include "token.h"

token_t get_token(string_t *src){
	string_t* type = string_new(3);
	type->data[0] = 'i';
	type->data[1] = 'n';
	type->data[2] = 't';

	if(string_match(src, type)){
		printf("int");
	}
}
