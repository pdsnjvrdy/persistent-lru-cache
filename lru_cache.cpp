#include "lru_cache.h"

LRUCache::LRUCache(size_t cap) : capacity(cap) {}

void LRUCache::put(int key, int value) {
    // if key already exists, update value and move to front
    auto it = map.find(key);
    if (it != map.end()) {
        it->second->second = value;
        items.splice(items.begin(), items, it->second);
        return;
    }

    // if full, evict the least recently used (back of list)
    if (items.size() == capacity) {
        int lru_key = items.back().first;
        map.erase(lru_key);
        items.pop_back();
    }

    // insert new item at front
    items.push_front({key, value});
    map[key] = items.begin();
}

bool LRUCache::get(int key, int &value) {
    auto it = map.find(key);
    if (it == map.end()) return false;

    // move the accessed item to front
    items.splice(items.begin(), items, it->second);
    value = it->second->second;
    return true;
}