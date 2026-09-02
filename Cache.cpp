
#include "Cache.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

// LRUCache
LRUCache::LRUCache(int cap) : Cache(cap) {}
void LRUCache::put(int key, int value) {
    if (kv.find(key) != kv.end()) {
        order.erase(keyIter[key]);
    } else if ((int)kv.size() == capacity) {
        int old = order.back();
        order.pop_back();
        kv.erase(old);
        keyIter.erase(old);
    }
    order.push_front(key);
    keyIter[key] = order.begin();
    kv[key] = value;
}
int LRUCache::get(int key) {
    if (kv.find(key) == kv.end()) return -1;
    order.erase(keyIter[key]);
    order.push_front(key);
    keyIter[key] = order.begin();
    return kv[key];
}
bool LRUCache::exists(int key) {
    return kv.find(key) != kv.end();
}

// LFUCache
LFUCache::LFUCache(int cap) : Cache(cap) {}
void LFUCache::put(int key, int value) {
    if (kv.find(key) != kv.end()) {
        kv[key] = value;
        freq[key]++;
        return;
    }
    if ((int)kv.size() == capacity) {
        int minFreq = INT_MAX, victim = -1;
        for (auto& p : freq) {
            if (kv.find(p.first) != kv.end() && p.second < minFreq) {
                minFreq = p.second;
                victim = p.first;
            }
        }
        if (victim != -1) {
            kv.erase(victim);
            freq.erase(victim);
        }
    }
    kv[key] = value;
    freq[key] = 1;
}
int LFUCache::get(int key) {
    if (kv.find(key) == kv.end()) return -1;
    freq[key]++;
    return kv[key];
}
bool LFUCache::exists(int key) {
    return kv.find(key) != kv.end();
}

// FIFOCache
FIFOCache::FIFOCache(int cap) : Cache(cap) {}
void FIFOCache::put(int key, int value) {
    if (kv.find(key) != kv.end()) {
        kv[key] = value;
        return;
    }
    if ((int)kv.size() == capacity) {
        int old = order.front();
        order.pop();
        kv.erase(old);
    }
    kv[key] = value;
    order.push(key);
}
int FIFOCache::get(int key) {
    if (kv.find(key) == kv.end()) return -1;
    return kv[key];
}
bool FIFOCache::exists(int key) {
    return kv.find(key) != kv.end();
}

// RandomCache
RandomCache::RandomCache(int cap) : Cache(cap) {}
void RandomCache::put(int key, int value) {
    if (kv.find(key) != kv.end()) {
        kv[key] = value;
        return;
    }
    if ((int)kv.size() == capacity) {
        int idx = rand() % keys.size();
        int victim = keys[idx];
        kv.erase(victim);
        keys.erase(keys.begin() + idx);
    }
    kv[key] = value;
    keys.push_back(key);
}
int RandomCache::get(int key) {
    if (kv.find(key) == kv.end()) return -1;
    return kv[key];
}
bool RandomCache::exists(int key) {
    return kv.find(key) != kv.end();
}
