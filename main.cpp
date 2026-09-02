
#include "Cache.h"
#include <iostream>
#include <cassert>
using namespace std;

void testLRU() {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    assert(cache.get(1) == 10);
    cache.put(3, 30); // evicts 2
    assert(cache.get(2) == -1);
    assert(cache.get(3) == 30);
    cache.put(4, 40); // evicts 1
    assert(cache.get(1) == -1);
    assert(cache.get(4) == 40);
    cout << "LRUCache passed\n";
}

void testLFU() {
    LFUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.get(1); // freq 1:2, 2:1
    cache.put(3, 30); // evicts 2
    assert(cache.get(2) == -1);
    assert(cache.get(1) == 10);
    assert(cache.get(3) == 30);
    cache.put(4, 40); // evicts 3
    assert(cache.get(3) == -1);
    assert(cache.get(4) == 40);
    cout << "LFUCache passed\n";
}

void testFIFO() {
    FIFOCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30); // evicts 1
    assert(cache.get(1) == -1);
    assert(cache.get(2) == 20);
    assert(cache.get(3) == 30);
    cache.put(4, 40); // evicts 2
    assert(cache.get(2) == -1);
    assert(cache.get(4) == 40);
    cout << "FIFOCache passed\n";
}

void testRandom() {
    RandomCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30); // evicts random
    int found = cache.get(1) + cache.get(2) + cache.get(3);
    int count = (cache.get(1) != -1) + (cache.get(2) != -1) + (cache.get(3) != -1);
    assert(count == 2);
    cache.put(4, 40); // evicts random
    count = (cache.get(1) != -1) + (cache.get(2) != -1) + (cache.get(3) != -1) + (cache.get(4) != -1);
    assert(count == 2);
    cout << "RandomCache passed\n";
}

int main() {
    testLRU();
    testLFU();
    testFIFO();
    testRandom();
    cout << "All tests passed!\n";
    return 0;
}
