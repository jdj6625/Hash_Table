# Hash Table (C Implementation)

A fixed-size hash table written in C using separate chaining (linked lists) for collision resolution. This project demonstrates manual memory management, pointer handling, and modular C design using CMake.

## Overview

This project implements a simple hash table that maps string keys to integer values. It includes operations for creating and deleting a hash table, inserting, removing, and searching for keys, a string-based hash function (polynomial rolling hash), and automated tests using `assert()` in `test_hash_table.c`.

## Design Highlights

### Data Structure
- **Collision Resolution:** Separate chaining with doubly-linked lists (`LinkedList`)
- **Hash Function:** Polynomial rolling hash using base 31 and modulo table capacity
- **Fixed Capacity:** Defined by `HT_SIZE` in `hash_table.h`
- **Error Sentinel:** `INT_MIN` is reserved to indicate "key not found" or error

### Memory Management
- Each bucket node (`LinkedList`) dynamically allocates memory for its key using `strdup()`
- Keys and nodes are freed in `deleteHT()` and `removeHT()` to prevent memory leaks
- All heap allocations are checked for `NULL` before use

### Design Choices
- **`strcmp` instead of `strncmp`:** Ensures full string comparison and avoids truncation collisions
- **Key Duplication:** Each key is copied to prevent dangling pointers if the caller frees their strings
- **File Separation:**  
  - `hash_table.c` / `hash_table.h`: Core hash table logic  
  - `linked_list.c` / `linked_list.h`: Supporting linked list structure  
  - `test_hash_table.c`: Assertion-based testing

## Building with CMake

### Requirements
- CMake 3.10 or newer  
- A C compiler (GCC, Clang, or MSVC) with C99 support

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/jdj6625/Hash_Table.git
cd Hash_Table

# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the executable
cmake --build .

# Run the program
./Hash_Table
```

### Example CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(Hash_Table C)
set(CMAKE_C_STANDARD 99)
add_executable(Hash_Table
    main.c
    hash_table.c
    hash_table.h
    linked_list.c
    linked_list.h
    test_hash_table.c
)
```

## Running Tests

The file `test_hash_table.c` includes automated checks using `assert()` to verify correctness and edge cases.  
Run the compiled binary to execute all tests.

```bash
./Hash_Table
```

### Expected Output
```
Basic insert and search test passed
Update existing key test passed
Remove existing key test passed
Remove nonexistent key test passed
Empty and special key test passed
Case sensitivity test passed
Zero and negative value test passed
Long key test passed
Hash function stability test passed
Delete then reuse test passed
All HashTable tests passed successfully.
```

If a test fails, the program prints detailed information such as:
```
Assertion failed in Case sensitivity test:
  Key: "hello"
  Expected: 2
  Got: 1
```

## Example Usage
```c
#include "hash_table.h"
#include <stdio.h>

int main(void) {
    HashTable ht = createHT();
    insertHT(&ht, "Hello", 42);
    int value = searchHT(&ht, "Hello");
    printf("Value of Hello: %d\n", value);
    deleteHT(&ht);
    return 0;
}
```

**Output:**
```
Value of Hello: 42
```

## Possible Extensions
- Dynamic resizing based on load factor
- Support for generic key/value types using `void*`
- User-defined hash function support
- Load factor and collision statistics
- Thread-safe access using locks or atomics

## License
This project is released under the MIT License. You may use, modify, and distribute it freely for educational or personal purposes.

## Author
**Jonathan Jacobs**  
Computer Engineering Student at Rochester Institute of Technology  
Developed as a modular data structures exercise in C.
