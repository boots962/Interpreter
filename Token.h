#ifndef Token_H
#define MAX_LENGTH 100

typedef enum {
	TOKEN_NUMBER, TOKEN_PLUS, TOKEN_MINUS, TOKEN_OPERATOR,
	TOKEN_IDENTIFIER,TOKEN_KEYWORD,
	TOKEN_EOF
} TokenType;

typedef struct{
	TokenType type;
	char lex[MAX_LENGTH];
	int val;
}Token;

#endif
