#include <stdio.h>
#include <stdbool.h>

#include "Token.h"
#define MAX_SIZE 100

typedef struct {
	Token seq[MAX_SIZE];
	int top;
}Stack;

//init stack
void init(Stack *stack){
	stack -> top = -1;
}


//checks if stack is empty
bool isEmpty(Stack *stack){
	return stack->top = -1;
}

//checks if stack is full
bool isFull(Stack *stack){
	return stack->top >= MAX_SIZE -1;
}

//pushes top value in stack
void push(Stack *stack, Token val){
	if (isFull(stack)){
		printf("Stack overflow\n");
		return;
	}
	stack->seq[++stack->top] = val;
	printf("pushed\n");
}

//pops top value in stack and returns it
Token pop(Stack *stack) {
	if(isEmpty(stack)){
		printf("Stack underflow");
		Token empty;
		empty.type = TOKEN_EOF;
		empty.lex[0] = '\0';
		empty.val = 0;
		return empty;
	}
	Token popped = stack->seq[stack->top];
	stack->top--;
	printf("Popped");
}

//returns top value in stack
Token peek(Stack *stack){
	if(isEmpty(stack)){
		printf("Stack is empty");
		Token empty;
                empty.type = TOKEN_EOF;
                empty.lex[0] = '\0';
                empty.val = 0;
                return empty;

	}
	return stack->seq[stack->top];
}


