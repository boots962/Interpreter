#include "Token.h"
#include <stdbool.h>

Token tokens[100];
int token_count = 0;

bool isNumber(char c);
bool isOperator(char c);
bool isIdentifier(char c);
bool isKeyword(char* str);
bool isWhitespace(char c);
char* getSubstring(char* str, int start, int end);
Token* lexer(char* input);

