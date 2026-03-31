
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "Parser.h"

#define MAX_LENGTH 100
/* Jack Gelinas's interpreter */

/*checks for integet value from a string
return true if integer, false otherwise*/
bool isInteger(char* str){
	if (str == NULL || *str == '\0'){
		return false;
	}
	int i = 0;
	while(isdigit(str[i])){ //check if char at is a digit
		i++;
	}
	return str[i] == '\0'; //if we reached the end of the string return true, else we reached a char that is not an int
}

/*checks if we reach a delimiter where data is separated from other data*/
bool isDelimiter(char chr){
	 return (chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}');
}

//check if data is an operator
bool isOperator(char chr){
	    return (chr =='+' || chr=='-'||chr == '*'
            || chr == '/' || chr == '>' || chr == '<'
            || chr == '=');
}

//returns if an identifier is valid
bool isValid(char*str){
	return (str[0] != '0' && str[0] != '1' && str[0] != '2'
            && str[0] != '3' && str[0] != '4'
            && str[0] != '5' && str[0] != '6'
            && str[0] != '7' && str[0] != '8'
            && str[0] != '9' && !isDelimiter(str[0]));
}


//returns if substr is a keyword identifier
bool isKeyword(char* key){
	const char* keywords[]
        = { "auto",     "break",    "case",     "char",
            "const",    "continue", "default",  "do",
            "double",   "else",     "enum",     "extern",
            "float",    "for",      "goto",     "if",
            "goon",      "long",     "register", "return",
            "short",    "signed",   "sizeof",   "static",
            "struct",   "switch",   "typedef",  "union",
            "unsigned", "void",     "volatile", "while" };
	for(int i = 0; i<sizeof(keywords)/sizeof(keywords[0]); i++){
		if(strcmp(keywords[i], key)==0){
			return true;
		}
	}
return false;
}


/* gets a substring from index start to
index end in a string */
char* getSubstring(char* str, int start, int end){
        int length = strlen(str);
        int subLength = end - start+1;
        char* subStr = (char*)malloc((subLength+1)*sizeof(char));
        strncpy(subStr, str+start, subLength);
        subStr[subLength] = '\0';
        return subStr;
}


/* The lexer, this will loop through the commands,
and it will tokenize all important data, if it is an int, identifier
etc, and it will send the data to the parser */
Stack* lexer(char* command){
	Stack* tokens = (Stack*)malloc(sizeof(Stack));
	init(tokens);
	int right = 0, left = 0;
	int length = strlen(command);
	while(right <=length && left <=right){
		Token currentToken;
		if(!isDelimiter(command[right])){
			right++;
		}

		if(isDelimiter(command[right]) && left == right){
			if(isOperator(command[right])){
				if(command[right] == '+') currentToken.type = TOKEN_PLUS;
				else if(command[right] == '-') currentToken.type = TOKEN_MINUS;
				else currentToken.type = TOKEN_OPERATOR;
				currentToken.lex[0] = command[right];
				currentToken.val = 0;
				push(tokens,currentToken);
			}
			right++;
			left = right;
		}
		else if(isDelimiter(command[right]) && left != right || (right == length && left != right)){
			char* substr = getSubstring(command, left, right-1);
			if(isKeyword(substr)){
			currentToken.type = TOKEN_KEYWORD;
			strcpy(currentToken.lex, substr);
			currentToken.val = 0;
			push(tokens,currentToken);
			}
			else if(isInteger(substr)){
			currentToken.type = TOKEN_NUMBER;
			strcpy(currentToken.lex,substr);
			currentToken.val = atoi(substr);
			push(tokens,currentToken);
			}
			else if(isValid(substr) &&!isDelimiter(command[right-1])){
			currentToken.type = TOKEN_IDENTIFIER;
			strcpy(currentToken.lex,substr);
			currentToken.val = 0;
			push(tokens,currentToken);
			}
			else if(!isValid(substr) && !isDelimiter(command[right-1])) printf("Un identified token");
			left = right;
		}
	}
	return tokens;
}

/*reads input from line*/
int read_line(char str[], int n){
	int ch, i=0;
	while((ch = getchar())!= '\n'){
		if (i<n-1){
			str[i++] = ch;
		}
	}
	str[i] = '\0';
	return i;
}

/* main function that is going to
run the loop for the lexer and syntax */
int main(void){
	char command[MAX_LENGTH];
	Stack*activationStack = (Stack*)malloc(sizeof(Stack));
	init(activationStack);
	while(true){
		printf("\n>>> ");
		read_line(command,MAX_LENGTH);
		if(strcmp(command, "clear")==0) return 0;
		if(strcmp(command, "quit")==0) return 0;
		Stack* parsing =  lexer(command);
		if(!isEmpty(parsing)){
			Stack*eval = parse(parsing, activationStack);
			if(!isEmpty(eval)){
			printf("\n%d",pop(eval).val);
			}
		}
		else printf("Empty stack");
	}
	return 0;
}

