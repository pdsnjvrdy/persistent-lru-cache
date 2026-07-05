#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>

class LRUCache {
    size_t capacity;
    std::list<std::pair<int, int>> items;            
    std::unordered_map<int, decltype(items.begin())> map;

public:
    LRUCache(size_t cap);
    void put(int key, int value);
    bool get(int key, int &value);   // returns false if not found
};

#endif