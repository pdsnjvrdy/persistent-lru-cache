#include "lru_cache.h"
#include <fstream>

void LRUCache::put_no_log(int key, int value) {
    auto it = map.find(key);
    if (it != map.end()) {
        it->second->second = value;
        items.splice(items.begin(), items, it->second);
        return;
    }

    if (items.size() == capacity) {
        int lru_key = items.back().first;
        map.erase(lru_key);
        items.pop_back();
    }

    items.push_front({key, value});
    map[key] = items.begin();
}

LRUCache::LRUCache(size_t cap, const std::string &wal_path)
    : capacity(cap), wal(wal_path)
{
    auto entries = WALManager::recover_from_file(wal_path);
    for (auto &kv : entries) {
        put_no_log(kv.first, kv.second);
    }
    // wal remains open in append mode, old entries are kept
}

void LRUCache::put(int key, int value) {
    // if key already exists, update value and move to front
    auto it = map.find(key);
    if (it != map.end()) {
        it->second->second = value;
        items.splice(items.begin(), items, it->second);
        // log the update
        wal.append_put(key, value);
        return;
    }

    // if full, evict the least recently used
    if (items.size() == capacity) {
        int lru_key = items.back().first;
        map.erase(lru_key);
        items.pop_back();
    }

    // insert new item at front
    items.push_front({key, value});
    map[key] = items.begin();

    // log the new entry
    wal.append_put(key, value);
}

bool LRUCache::get(int key, int &value) {
    auto it = map.find(key);
    if (it == map.end()) return false;

    // move the accessed item to front
    items.splice(items.begin(), items, it->second);
    value = it->second->second;
    return true;
}