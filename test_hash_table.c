#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

static void expect_value(HashTable* ht, const char* key, int expected, const char* test_name) {
    int got = searchHT(ht, key);
    if (got != expected) {
        fprintf(stderr,
            "Assertion failed in %s:\n"
            "  Key: \"%s\"\n"
            "  Expected: %d\n"
            "  Got: %d\n",
            test_name, key, expected, got);
        abort();
    }
}

static void test_basic_insert_search(void) {
    HashTable ht = createHT();
    insertHT(&ht, "Hello", 42);
    expect_value(&ht, "Hello", 42, "Basic insert and search test");
    insertHT(&ht, "World", 7);
    expect_value(&ht, "World", 7, "Basic insert and search test");
    expect_value(&ht, "Hello", 42, "Basic insert and search test");
    deleteHT(&ht);
    printf("Basic insert and search test passed\n");
}

static void test_update_existing_key(void) {
    HashTable ht = createHT();
    insertHT(&ht, "dup", 1);
    expect_value(&ht, "dup", 1, "Update existing key test");
    insertHT(&ht, "dup", 999);
    expect_value(&ht, "dup", 999, "Update existing key test");
    deleteHT(&ht);
    printf("Update existing key test passed\n");
}

static void test_remove_existing_key(void) {
    HashTable ht = createHT();
    insertHT(&ht, "rm", 123);
    expect_value(&ht, "rm", 123, "Remove existing key test");
    removeHT(&ht, "rm");
    expect_value(&ht, "rm", INT_MIN, "Remove existing key test");
    deleteHT(&ht);
    printf("Remove existing key test passed\n");
}

static void test_remove_nonexistent_key_is_noop(void) {
    HashTable ht = createHT();
    removeHT(&ht, "missing");
    insertHT(&ht, "k", 5);
    expect_value(&ht, "k", 5, "Remove nonexistent key test");
    deleteHT(&ht);
    printf("Remove nonexistent key test passed\n");
}

static void test_empty_key_and_special_chars(void) {
    HashTable ht = createHT();
    insertHT(&ht, "", 11);
    expect_value(&ht, "", 11, "Empty and special key test");
    insertHT(&ht, "sp@ce key", 21);
    expect_value(&ht, "sp@ce key", 21, "Empty and special key test");
    insertHT(&ht, "with\nnewline", 33);
    expect_value(&ht, "with\nnewline", 33, "Empty and special key test");
    deleteHT(&ht);
    printf("Empty and special key test passed\n");
}

static void test_case_sensitivity(void) {
    HashTable ht = createHT();
    insertHT(&ht, "Hello", 1);
    insertHT(&ht, "hello", 2);
    expect_value(&ht, "Hello", 1, "Case sensitivity test");
    expect_value(&ht, "hello", 2, "Case sensitivity test");
    deleteHT(&ht);
    printf("Case sensitivity test passed\n");
}

static void test_zero_and_negative_values(void) {
    HashTable ht = createHT();
    insertHT(&ht, "zero", 0);
    expect_value(&ht, "zero", 0, "Zero and negative value test");
    insertHT(&ht, "neg", -1234567);
    expect_value(&ht, "neg", -1234567, "Zero and negative value test");
    insertHT(&ht, "almost_min", INT_MIN + 1);
    expect_value(&ht, "almost_min", INT_MIN + 1, "Zero and negative value test");
    deleteHT(&ht);
    printf("Zero and negative value test passed\n");
}

static void test_long_key(void) {
    HashTable ht = createHT();
    char longkey[1024];
    memset(longkey, 'A', sizeof(longkey) - 1);
    longkey[sizeof(longkey) - 1] = '\0';
    insertHT(&ht, longkey, 77);
    expect_value(&ht, longkey, 77, "Long key test");
    deleteHT(&ht);
    printf("Long key test passed\n");
}

static void test_hash_function_stability(void) {
    HashTable ht = createHT();
    size_t h1 = hashFunction(&ht, "stable");
    size_t h2 = hashFunction(&ht, "stable");
    if (h1 != h2) {
        fprintf(stderr,
            "Assertion failed in Hash function stability test:\n"
            "  Same key produced different hashes (%zu vs %zu)\n",
            h1, h2);
        abort();
    }
    (void)hashFunction(&ht, "stableX");
    deleteHT(&ht);
    printf("Hash function stability test passed\n");
}

static void test_delete_then_reuse(void) {
    HashTable ht = createHT();
    insertHT(&ht, "a", 1);
    insertHT(&ht, "b", 2);
    deleteHT(&ht);
    ht = createHT();
    insertHT(&ht, "c", 3);
    expect_value(&ht, "c", 3, "Delete then reuse test");
    deleteHT(&ht);
    printf("Delete then reuse test passed\n");
}