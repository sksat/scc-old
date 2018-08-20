#ifndef TOKEN_H_
#define TOKEN_H_

#include "string.h"
#include "util.h"

typedef enum {
	tInteger,
	tString,
	tChar,
} TokenType;

typedef struct {
	int type;
	string_t str;
} token_t;

token_t get_token(string_t* src);

#endif
