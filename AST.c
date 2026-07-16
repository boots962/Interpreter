#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

/*creates a literal node to store a value*/
ASTNode* create_literal_node(int value){
    //allocate memory for the node 
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if(node == NULL) return NULL;
    //set the type of the node
    node ->type = NODE_LITERAL;
    //assign value to the node
    node->as.literal.value = value;

    return node;
}


//create a binary node
ASTNode* create_binary_node(char op, ASTNode*left, ASTNode*right){
    //allocate memory for the ndoe
    ASTNode* node = malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;

    //assign type of node and all the appropriate values for the node
    node->type = NODE_BINARY;
    node->as.binary.left=left;
    node->as.binary.right=right;
    node->as.binary.op = op;

    return node;
}

ASTNode* create_ctrl_node(ASTNode* cond, ASTNode* then_b, ASTNode* else_b){
    ASTNode* node = malloc(sizeof(ASTNode));
    if(node == NULL) return NULL;

    node->type = NODE_CTRL;
    node->as.cond.cond = cond;
    node->as.cond.then_b = then_b;
    node->as.cond.else_b = else_b;

    return node;
}

ASTNode* create_decl_node(char* name, ASTNode* node){
    ASTNode* decl_node = malloc(sizeof(ASTNode));
    if(decl_node == NULL) return NULL;

    decl_node->type = NODE_DECL;
    decl_node->as.decl.name = name;
    decl_node->as.decl.init = node;

    return decl_node;
}

//recursivlely frees node
void freeNode(ASTNode* node){
    if(node == NULL) return;

    switch(node->type){
        case NODE_LITERAL:
            free(node);
            break;
        case NODE_BINARY:
            freeNode(node->as.binary.left);
            freeNode(node->as.binary.right);
            free(node);
            break;
        case NODE_CTRL:
            freeNode(node->as.cond.cond);
            freeNode(node->as.cond.then_b);
            freeNode(node->as.cond.else_b);
            free(node);
            break;
        case NODE_DECL:
            free(node->as.decl.name);
            freeNode(node->as.decl.init);
            break;
    }
}

int evaluate(ASTNode* node){
    
}