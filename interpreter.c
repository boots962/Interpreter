#include <stdio.h>
#include "Interpreter.h"

int main(void){
    char input[100];
    printf("\n>>> ");
    fgets(input, sizeof(input), stdin);

    Token* tokens = lexer(input);
    ASTNode* ast = parse(tokens);

    int result = evaluate(ast);
    printf("Result: %d\n", result);

    freeNode(ast);
    return 0;
}