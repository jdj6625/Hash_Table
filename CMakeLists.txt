cmake_minimum_required(VERSION 3.10)
project(Hash_Table C)

set(CMAKE_C_STANDARD 99)

add_executable(Hash_Table main.c
        hash_table.c
        hash_table.h
        linked_list.h
        linked_list.c
        test_hash_table.c
)
