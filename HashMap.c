#include "HashMap.h"

void initHashMap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        map->map[i] = NULL;
    }
}

unsigned int hash(const char* key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++) != 0) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

void insert(HashMap* map, const char* key, Token value) {
    unsigned int index = hash(key);
    Node* node = map->map[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    Node* newNode = malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = map->map[index];
    map->map[index] = newNode;
}

Token get(HashMap *map, const char* key) {
    unsigned int index = hash(key);
    Node* node = map->map[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    Token empty;
    empty.type = TOKEN_EOF;
    empty.lex[0] = '\0';
    empty.val = 0;
    return empty;
}

void removeEntry(HashMap* map, const char* key) {
    unsigned int index = hash(key);
    Node* node = map->map[index];
    Node* prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                map->map[index] = node->next;
            }
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}


