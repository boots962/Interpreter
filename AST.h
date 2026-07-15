#ifndef AST_H
#define AST_H

typedef enum{
    NODE_LITERAL,
    NODE_BINARY,
    NODE_CTRL,
    NODE_DECL
} NodeType;

typedef struct ASTNode{
    NodeType type;
    union {
        struct{
            int value;
        } literal;
        struct{
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binary;
    }as;
}ASTNode;

ASTNode* create_literal_node(int value);
ASTNode* create_binary_node(char op, ASTNode* left, ASTNode* right);
void freeNode(ASTNode* node);
int evaluate(ASTNode* node);
void printAST(ASTNode* node, int depth);

#endif AST_H