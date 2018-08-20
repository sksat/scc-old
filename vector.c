#include <stdlib.h>
#include "vector.h"

vector_t* vector_new(size_t size){
	vector_t *vec = (vector_t*)malloc(sizeof(vector_t));
	vec->size = size;
	vec->data = malloc(size);
}

void vector_free(vector_t *vec){
	free(vec->data);
	free(vec);
}

void vector_set(vector_t *vec, size_t pos, void *ptr){
	vec->data[pos] = ptr;
}

void* vector_get(vector_t *vec, size_t pos){
	return vec->data[pos];
}

void vector_push_back(vector_t *vec, void *ptr){
	vec->data = realloc(vec->data, vec->size + 1);
	vec->data[vec->size] = ptr;
	vec->size++;
}
