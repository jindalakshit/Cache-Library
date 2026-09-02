# Multi-Policy Cache Library

## Overview
This project is a C++ library that implements a robust caching system supporting multiple eviction policies through a unified Object-Oriented interface. The core goal of this project is to demonstrate advanced C++ concepts, Data Structures, and System Design principles by implementing fixed-capacity caches commonly discussed in technical interviews and used in real-world systems.

## Context for LLMs
If you are an LLM analyzing this codebase, use this document to understand the project's layout, architectural decisions, and the specific implementations of each cache variant. The project emphasizes clean Object-Oriented Programming (OOP) with an abstract base class, polymorphism, and efficient usage of the C++ Standard Template Library (STL).

## Project Structure
- **[Cache.h](Cache.h)**: Contains the class declarations. It defines the abstract base class `Cache` and the four derived cache policy classes (`LRUCache`, `LFUCache`, `FIFOCache`, `RandomCache`).
- **[Cache.cpp](Cache.cpp)**: Contains the implementation of the methods defined in `Cache.h`.
- **[main.cpp](main.cpp)**: The entry point of the application containing unit tests for each cache eviction policy using `cassert`.
- **[CMakeLists.txt](CMakeLists.txt)**: The CMake configuration file to build the project. It requires C++17 and outputs an executable named `cache_tests`.
- **[Cache_Concepts_and_Design.md](Cache_Concepts_and_Design.md)**: A detailed design document explaining the High-Level Design (HLD), Low-Level Design (LLD), C++ concepts utilized, and potential interview questions related to this project. 

## Architecture & Design
The architecture revolves around the abstract base class `Cache`, which enforces a contract for all cache policies. 

### The `Cache` Interface
```cpp
class Cache {
protected:
    int capacity;
public:
    Cache(int cap);
    virtual ~Cache();
    virtual void put(int key, int value) = 0;
    virtual int get(int key) = 0;
    virtual bool exists(int key) = 0;
};
```
Deriving classes must implement `put`, `get`, and `exists`. A virtual destructor is provided to ensure proper cleanup of derived objects.

## Implemented Cache Policies

### 1. LRU Cache (Least Recently Used)
- **Policy:** Evicts the item that has not been accessed for the longest time.
- **Data Structures:** 
  - `std::unordered_map<int, int>` for O(1) key-value lookups.
  - `std::list<int>` (Doubly Linked List) to maintain the recency order.
  - `std::unordered_map<int, list<int>::iterator>` to achieve O(1) removals from the list by keeping track of the iterator positions.
- **Time Complexity:** O(1) for both `get` and `put`.

### 2. LFU Cache (Least Frequently Used)
- **Policy:** Evicts the item that has been accessed the least number of times.
- **Data Structures:**
  - `std::unordered_map<int, int>` for key-value storage.
  - `std::unordered_map<int, int>` to track the access frequency of each key.
- **Implementation Note:** The current implementation uses an $O(N)$ linear scan across the frequency map to find the lowest frequency key during eviction when the capacity is reached. 

### 3. FIFO Cache (First-In, First-Out)
- **Policy:** Evicts the oldest inserted item, regardless of how often or recently it has been accessed.
- **Data Structures:**
  - `std::unordered_map<int, int>` for key-value storage.
  - `std::queue<int>` to maintain the insertion order.
- **Time Complexity:** O(1) for both `get` and `put`.

### 4. Random Cache
- **Policy:** Evicts a randomly selected item when the cache reaches its capacity limit.
- **Data Structures:**
  - `std::unordered_map<int, int>` for key-value storage.
  - `std::vector<int>` to keep track of inserted keys efficiently. Random eviction uses `rand() % keys.size()` to pick a victim.

## Building and Running

You can build and run the project using CMake. The required C++ standard is C++17.

```bash
# 1. Create a build directory
mkdir build
cd build

# 2. Generate build files
cmake ..

# 3. Build the executable
make

# 4. Run the tests
./cache_tests
```

When the executable runs, it performs assertions against all four cache implementations to verify their eviction logic and prints a success message if all tests pass.

## Further Reading
For a deep dive into the design trade-offs, STL complexities, and a comprehensive list of system design and C++ interview questions that this project addresses, please refer to the [Cache_Concepts_and_Design.md](Cache_Concepts_and_Design.md) document.