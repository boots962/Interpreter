#include "HashMap.h"

unsigned int hash(const char* key){
	unsigned int hash = 5381;
	int c;
	while ((c = *key++) != 0) {
		hash = ((hash<<5)+hash)+c;
	}
	return hash%TABLE_SIZE;
}

void insert(HashMap* map, const char* key, Token value){
	unsigned int index = hash(key);
	Node* newNode = malloc(sizeof(Node));
	newNode -> key = strdup(key);
	newNode -> value = value;
	newNode -> next = map->map[index];
	map->map[index] = newNode;
}

