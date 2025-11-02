#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#include <stdio.h>
#define STR_SIZE 1024

HashTable createHT(void)
{
   return (HashTable){
      .capacity = HT_SIZE,
   };
}

void deleteHT(HashTable* hash_table)
{
   for (int i=0; i<hash_table->capacity; i++)
   {
      LinkedList* bucket = hash_table->buckets[i];
      while (bucket != NULL)
      {
         LinkedList* next = bucket->next;
         free(bucket->key);
         free(bucket);
         bucket = next;
      }
   }
}

size_t hashFunction(HashTable* ht, const char* key)
{
   size_t hash = 0;
   const size_t prime = 31;
   for (int i = 0; key[i] != '\0'; i++)
      hash = hash * prime + (unsigned char)key[i];
   return hash % ht->capacity;
}


void insertHT(HashTable* ht, const char* key, int value)
{
   size_t index = hashFunction(ht, key);
   if (ht->buckets[index] == NULL)
   {
      ht->buckets[index] = malloc(sizeof(LinkedList));
      if (ht->buckets[index] == NULL)
      {
         fprintf(stderr, "Error: Failed to allocate node for entry\n");
         return;
      }
      ht->buckets[index]->prev = NULL;
      ht->buckets[index]->key = _strdup(key);
      ht->buckets[index]->value = value;
      ht->buckets[index]->next = NULL;
      return;
   }

   LinkedList* bucket = ht->buckets[index];
   while (bucket->next != NULL)
   {
      if ((strncmp(key, bucket->key, STR_SIZE) == 0))
      {
         bucket->value = value;
         return;
      }
      bucket = bucket->next;
   }
   if ((strncmp(key, bucket->key, STR_SIZE) == 0))
   {
      bucket->value = value;
      return;
   }

   bucket->next = malloc(sizeof(LinkedList));
   if (bucket->next == NULL)
   {
      fprintf(stderr, "Error: Failed to allocate node for entry\n");
      return;
   }

   bucket->next->prev = bucket;
   bucket = bucket->next;
   bucket-> key = _strdup(key);
   bucket->value = value;
   bucket->next = NULL;
}

void removeHT(HashTable* ht, const char* key)
{
   size_t index = hashFunction(ht, key);
   LinkedList* bucket = ht->buckets[index];
   while (bucket != NULL)
   {
      if (strncmp(key, bucket->key, STR_SIZE) == 0)
      {
         if (bucket->prev != NULL)
         {
            bucket->prev->next = bucket->next;
         }

         else
         {
            ht->buckets[index] = bucket->next;
         }
         if (bucket->next != NULL) bucket->next->prev = bucket->prev;
         free(bucket);
         return;
      }
      bucket = bucket->next;
   }
}

int searchHT(HashTable* ht, const char* key)
{
   size_t index = hashFunction(ht, key);
   LinkedList* bucket = ht->buckets[index];
   while (bucket != NULL)
   {
      if (strncmp(key, bucket->key, STR_SIZE) == 0)
      {
         return bucket->value;
      }
      bucket = bucket->next;
   }
   return INT_MIN;
}