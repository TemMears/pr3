#pragma once
#include "server.h"

typedef struct NodeHash {
    char* key;
    char* value;
    bool occupied;
} NodeHash;

typedef struct HashTable {
    NodeHash table[SIZE];
} HashTable;

int hash(const char* key);
int hash2(const char* key);
HashTable* createHashTable();
void printHashMap(const HashTable* hashTable);
bool addEntry(HashTable* hashTable, char* key, char* value);
char* getValue(HashTable* hashTable, char* key);
bool removeEntry(HashTable* hashTable, char* key);

char* pr2(char* str);
