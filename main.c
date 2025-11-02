#include <stdio.h>
#include "test_hash_table.c"

int main(void)
{
   test_basic_insert_search();
   test_update_existing_key();
   test_remove_existing_key();
   test_remove_nonexistent_key_is_noop();
   test_empty_key_and_special_chars();
   test_case_sensitivity();
   test_zero_and_negative_values();
   test_long_key();
   test_hash_function_stability();
   test_delete_then_reuse();
   printf("All HashTable tests passed.\n");
   return 0;
}