#pragma once

#include <unordered_map>
#include <list>
#include <queue>
#include <vector>

using namespace std;

class Cache {
protected:
    int capacity;
public:
    Cache(int cap) : capacity(cap) {}
    virtual ~Cache() {}
    virtual void put(int key, int value) = 0;
    virtual int get(int key) = 0;
    virtual bool exists(int key) = 0;
};

class LRUCache : public Cache {
    unordered_map<int, list<int>::iterator> keyIter;
    unordered_map<int, int> kv;
    list<int> order;
public:
    LRUCache(int cap);
    void put(int key, int value) override;
    int get(int key) override;
    bool exists(int key) override;
};

class LFUCache : public Cache {
    unordered_map<int, int> kv;
    unordered_map<int, int> freq;
public:
    LFUCache(int cap);
    void put(int key, int value) override;
    int get(int key) override;
    bool exists(int key) override;
};

class FIFOCache : public Cache {
    unordered_map<int, int> kv;
    queue<int> order;
public:
    FIFOCache(int cap);
    void put(int key, int value) override;
    int get(int key) override;
    bool exists(int key) override;
};

class RandomCache : public Cache {
    unordered_map<int, int> kv;
    vector<int> keys;
public:
    RandomCache(int cap);
    void put(int key, int value) override;
    int get(int key) override;
    bool exists(int key) override;
};
