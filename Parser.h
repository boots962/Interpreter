#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "Stack.h"


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


Stack* parse(Stack* stack){
	if(canReduce(stack)){
		Token right = pop(stack);
		Token op = pop(stack);
		Token left = pop(stack);
		push(stack, combinedResult(left,op,right));
	}
	return stack;
}

