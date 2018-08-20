#include "token.h"
#include "vector.h"

vector_t *types;

void init_token(){
	static char* default_types[2] = {
		"char",
		"int",
	};
	types = vector_new(0);

	size_t i;
	for(i=0; i<2; i++){
		vector_push_back(types, to_string(default_types[i]));
	}

	printf("default type list:\n");
	for(i=0;i<types->size;i++){
		printf("\t");
		string_print(vector_get(types, i));
		printf("\n");
	}
}

token_t get_token(string_t *src){
	size_t i;
	for(i=0; i<types->size; i++){
		string_t *t = vector_get(types, i);
		if(string_match(src, t)){
				printf("match: %s\n", t->data);
		}
	}
}
