#ifndef HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Token.h"

#define TABLE_SIZE 100

typedef struct Node{
	char* key;
	int value;
	struct Node* next;
} Node;

typedef struct{
	Node* map[TABLE_SIZE];
} HashMap;

unsigned int hash(const char* key);
void insert(HashMap*Map, const char* key, Token value);
Token get(HashMap *map, char*key);
void remove(HashMap* map, char*key);

#endif
