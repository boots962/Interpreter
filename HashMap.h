#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Token.h"

#define TABLE_SIZE 100

typedef struct Node {
    char* key;
    Token value;
    struct Node* next;
} Node;

typedef struct {
    Node* map[TABLE_SIZE];
} HashMap;

void initHashMap(HashMap *map);
unsigned int hash(const char* key);
void insert(HashMap* map, const char* key, Token value);
Token get(HashMap *map, const char* key);
void removeEntry(HashMap* map, const char* key);

#endif
