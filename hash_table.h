#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include "linked_list.h"
#define HT_SIZE 10

typedef struct HashTable
{
   size_t capacity;
   LinkedList* buckets[HT_SIZE];
} HashTable;

HashTable createHT(void);
void deleteHT(HashTable* hash_table);
size_t hashFunction(HashTable* ht, const char*);

void removeHT(HashTable* ht, const char* key);
void insertHT(HashTable* ht, const char* key, int value);
int searchHT(HashTable* ht, const char* key);

#endif //HASH_TABLE_HASH_TABLE_H