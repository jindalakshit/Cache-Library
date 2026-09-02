# Multi-Policy Cache Library: Concepts, Design, and Interview Prep

## High-Level Design (HLD)

- **Goal:** Implement a cache library supporting multiple eviction policies (LRU, LFU, FIFO, Random) with a unified interface.
- **Architecture:**
  - `Cache` (abstract base class)
    - `LRUCache`
    - `LFUCache`
    - `FIFOCache`
    - `RandomCache`
- **Key Methods:**
  - `put(key, value)`
  - `get(key)`
  - `exists(key)`
- **Fixed Capacity:** Each cache has a maximum number of items.

## Low-Level Design (LLD)

### Common Elements
- **Abstract Base Class:** `Cache` defines the interface and stores `capacity`.
- **Inheritance:** Each policy is a derived class.
- **Polymorphism:** Virtual methods allow using different caches via base class pointers.

### Policy Implementations
- **LRUCache:**
  - `unordered_map<int, list<int>::iterator>` for fast lookup and position tracking
  - `unordered_map<int, int>` for key-value storage
  - `list<int>` for access order (most recent at front)
- **LFUCache:**
  - `unordered_map<int, int>` for key-value storage
  - `unordered_map<int, int>` for frequency counts
  - Linear scan to find least frequently used key
- **FIFOCache:**
  - `unordered_map<int, int>` for key-value storage
  - `queue<int>` for insertion order
- **RandomCache:**
  - `unordered_map<int, int>` for key-value storage
  - `vector<int>` for random eviction

## C++ Concepts Used

### Object-Oriented Programming (OOP)
- **Abstraction:** Abstract base class with pure virtual functions
- **Inheritance:** Derived classes for each policy
- **Polymorphism:** Virtual functions and override
- **Encapsulation:** Data members are protected/private
- **Constructor/Destructor:** Proper initialization and cleanup

### STL Containers
- **unordered_map:** Hash table for O(1) lookup
- **list:** Doubly linked list for LRU
- **queue:** FIFO order
- **vector:** Random access for RandomCache
- **iterator:** Used for efficient element manipulation

### C++ Features
- **using namespace std:** Avoids std:: prefix
- **Override specifier:** Ensures correct overriding
- **Access specifiers:** public, protected
- **Member initializer list:** Used in constructors
- **Pragma once:** Header guard

## Computer Science/Data Structure Concepts
- **Cache Design:** Eviction policies, fixed capacity
- **Hash Table:** Fast key-value storage
- **Doubly Linked List:** Maintains order for LRU
- **Queue:** Maintains order for FIFO
- **Vector:** Used for random eviction
- **Frequency Counter:** Used in LFU
- **Algorithmic Complexity:** O(1) for most operations, O(n) for LFU eviction

## Tricky Interview Questions
- Why use a virtual destructor in the base class?
- What happens if you don’t use override?
- How does LRU achieve O(1) eviction and update?
- Why is LFU eviction O(n)? How can it be improved?
- Trade-offs between eviction policies?
- How does RandomCache ensure uniform eviction probability?
- Risks of using `using namespace std;` in a header file?
- How to support generic types (templates)?
- How to make this thread-safe?
- Memory overheads of each policy?
- How does encapsulation help?
- Why use protected for capacity?
- Difference between public, protected, and private inheritance?
- How does polymorphism work at runtime?
- Purpose of pure virtual functions?
- STL list vs vector performance and use case?
- Shallow vs deep copy in C++?
- Big-O complexity of each operation?
- How to test for correctness and edge cases?
- What happens if you call get() on a missing key?
- How to extend for time-based eviction?
- Issues with storing iterators in a map (as in LRU)?
- Handling duplicate keys in FIFO or RandomCache?
- Difference between queue and deque?
- Why is the base class constructor called in the derived class initializer list?
- Effect of not marking methods as virtual in the base class?
- How does the compiler know which derived method to call at runtime?
- Stack vs heap allocation for these objects?
- Effect of not having a virtual destructor in the base class?

## Testing
- Each policy is tested independently
- Eviction logic is verified
- Edge cases: empty cache, single item, full cache

---

This file covers all design, implementation, and interview-relevant concepts for the multi-policy cache project.
