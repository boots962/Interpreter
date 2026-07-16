#include "Lexer.h"

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool isAssign(char c){
    return c == '=';
}

bool isIdentifier(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool isKeyword(char* str){
    return strcmp(str, "if") == 0 || strcmp(str, "else") == 0 || strcmp(str, "while") == 0 || strcmp(str, "for") == 0 || strcmp(str, "return") == 0;
}

bool isWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

char* getSubstring(char* str, int start, int end){
    int length = end - start;
    char* substr = (char*)malloc(length + 1);
    strncpy(substr, str + start, length);
    substr[length] = '\0';
    return substr;
}

Token* lexer(char* input){
    int length = strlen(input);
    int i = 0;
    while(i < length){
        if(isWhitespace(input[i])){
            i++;
            continue;
        }
        if(isNumber(input[i])){
            int start = i;
            while(i < length && isNumber(input[i])){
                i++;
            }
            char* lexeme = getSubstring(input, start, i);
            tokens[token_count].type = TOKEN_NUMBER;
            strcpy(tokens[token_count].lex, lexeme);
            tokens[token_count].val = atoi(lexeme);
            token_count++;
            free(lexeme);
        } else if(isOperator(input[i])){
            tokens[token_count].type = TOKEN_OPERATOR;
            tokens[token_count].lex[0] = input[i];
            tokens[token_count].lex[1] = '\0';
            token_count++;
            i++;
        } else if(isIdentifier(input[i])){
            int start = i;
            while(i < length && (isIdentifier(input[i]) || isNumber(input[i]))){
                i++;
            }
            char* lexeme = getSubstring(input, start, i);
            if(isKeyword(lexeme)){
                tokens[token_count].type = TOKEN_KEYWORD;
            } else {
                tokens[token_count].type = TOKEN_IDENTIFIER;
            }
            strcpy(tokens[token_count].lex, lexeme);
            token_count++;
            free(lexeme);
        } else if(isAssign(input[i])){
            tokens[token_count].type = TOKEN_ASSIGN;
            tokens[token_count].lex[0] = input[i];
            tokens[token_count].lex[1] = '\0';
            token_count++;
            i++;
        } else {
            printf("Unknown character: %c\n", input[i]);
            i++;
        }
    }
    tokens[token_count].type = TOKEN_EOF;
    tokens[token_count].lex[0] = '\0';
    return tokens;
}
