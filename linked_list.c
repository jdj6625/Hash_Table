#include <stddef.h>
#include <stdio.h>
#include "linked_list.h"

void printLL(const LinkedList* list)
{
   while (list != NULL)
   {
      printf("Node: %s\nValue: %d\n", list->key, list->value);
      list = list->next;
   }
}
