#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "Stack.h"
#include "Integer.h"
#include "HashMap.h"

Token combinedResult(Token left, Token op, Token right);
bool canReduce(Stack *stack);
bool isInitialize(Stack *stack);
Token createIdentifier(Token type, Token iden, Token val);
Stack* parse(Stack* stack, HashMap* activationMap);




