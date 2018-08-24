#ifndef TOKEN_H_
#define TOKEN_H_

#include "string.h"
#include "util.h"

typedef enum {
	tUnknown,	// temporary
	tComment,
	tType,		// int,char
	tDigit,		// 10
	tString,	// "hoge"
	tChar,		// 'c'
	tDelim,		// ここから先はdelim_strに合わせる
	tBracketStart, tBracketEnd,	// (,)
	tBlockStart, tBlockEnd,		// {,}
	tSBracketStart, tSBracketEnd,// [,]
	tComma, tQuestion, tColon, tSemicolon, // , ? : ;
	tOperator,
} TokenType;

typedef struct {
	int type;
	string_t *str;
} token_t;

extern token_t space_token;

void init_token();
token_t* get_token(string_t* src);

bool is_assignment_token(token_t *tok);
size_t token_get_priority(token_t *tok);

const char* token_type2name(int type);

#endif
