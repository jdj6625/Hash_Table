#ifndef HASH_TABLE_LINKED_LIST_H
#define HASH_TABLE_LINKED_LIST_H

typedef struct LinkedList
{
   char* key;
   int value;
   struct LinkedList* next;
   struct LinkedList* prev;
} LinkedList;

void printLL(const LinkedList* list);

#endif //HASH_TABLE_LINKED_LIST_H