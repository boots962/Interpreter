#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "Stack.h"
#include "Integer.h"

Token combinedResult(Token left, Token op, Token right){
	Token res;
	res.type = TOKEN_NUMBER;

	if(op.type == TOKEN_PLUS){
		res.val = left.val+right.val;
	}
	if(op.type == TOKEN_MINUS){
		res.val = left.val-right.val;
	}
	return res;
}

bool canReduce(Stack *stack){
	if(stack->top<2) {return false; }
	if(stack->seq[stack->top].type == TOKEN_NUMBER &&
	  stack->seq[stack->top-1].type == TOKEN_PLUS &&
	  stack->seq[stack->top-2].type == TOKEN_NUMBER) return true;
	if(stack->seq[stack->top].type == TOKEN_NUMBER &&
	  stack->seq[stack->top-1].type == TOKEN_MINUS &&
	  stack->seq[stack->top-2].type == TOKEN_NUMBER) return true;
	return false;
}

bool isInitialize(Stack *stack){
	if(stack->top<3){return false;}
	if(stack->seq[stack->top].type == TOKEN_NUMBER &&
	  stack->seq[stack->top-1].type == TOKEN_OPERATOR &&
	  stack->seq[stack->top-2].type == TOKEN_IDENTIFIER &&
	  stack->seq[stack->top-3].type == TOKEN_KEYWORD){
	printf("Has been initialized\n");
	 return true;
	}
	return false;
}

Token createIdentifier(Token type, Token iden, Token val){
	Token var;
	var.type = type.type;
	strcpy(var.lex, iden.lex);
	var.val = val.val;
	return var;
}

Stack* parse(Stack* stack){
	Stack*activationStack = (Stack*)malloc(sizeof(Stack));
	init(activationStack);
	if(isInitialize(stack)){
		Token val = pop(stack);
		pop(stack);
		Token iden = pop(stack);
		Token type = pop(stack);
		push(activationStack, createIdentifier(type, iden, val));
	}

	if(canReduce(stack)){
		Token right = pop(stack);
		Token op = pop(stack);
		Token left = pop(stack);
		push(stack, combinedResult(left,op,right));
	}
	Token init = pop(activationStack);
	printf("%s = %d", init.lex, init.val);
	return stack;
}

