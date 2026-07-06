#include "lru_cache.h"
#include <iostream>
using namespace std;

int main() {
    bool all_pass = true;

    // Test 1: put and get
    {
        LRUCache cache(2, "test.wal");
        cache.put(1, 100);
        cache.put(2, 200);
        int val;
        if (!cache.get(1, val) || val != 100) {
            cout << "FAIL: basic get after put\n";
            all_pass = false;
        }
    }

    // Test 2: Eviction when capacity exceeded
    {
        LRUCache cache(2, "test.wal");
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(3, 300);  // should evict key 1
        int val;
        if (cache.get(1, val)) {
            cout << "FAIL: key 1 should have been evicted\n";
            all_pass = false;
        }
        if (!cache.get(2, val) || val != 200) {
            cout << "FAIL: key 2 should still exist\n";
            all_pass = false;
        }
        if (!cache.get(3, val) || val != 300) {
            cout << "FAIL: key 3 should exist\n";
            all_pass = false;
        }
    }

    // Test 3: Update existing key (should not evict)
    {
        LRUCache cache(2, "test.wal");
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(1, 111);           // update key 1
        cache.put(3, 300);           // should evict key 2 (LRU is key 2 now)
        int val;
        if (!cache.get(1, val) || val != 111) {
            cout << "FAIL: key 1 should be 111\n";
            all_pass = false;
        }
        if (cache.get(2, val)) {
            cout << "FAIL: key 2 should have been evicted\n";
            all_pass = false;
        }
        if (!cache.get(3, val) || val != 300) {
            cout << "FAIL: key 3 should exist\n";
            all_pass = false;
        }
    }

    // Test 4: get updates access order (LRU moves)
    {
        LRUCache cache(2, "test.wal");
        cache.put(1, 100);
        cache.put(2, 200);
        int dummy;
        cache.get(1, dummy);    // key 1 becomes most recent, key 2 is LRU
        cache.put(3, 300);      // should evict key 2
        int val;
        if (!cache.get(1, val) || val != 100) {
            cout << "FAIL: key 1 should still exist after LRU update\n";
            all_pass = false;
        }
        if (cache.get(2, val)) {
            cout << "FAIL: key 2 should have been evicted\n";
            all_pass = false;
        }
        if (!cache.get(3, val) || val != 300) {
            cout << "FAIL: key 3 should exist\n";
            all_pass = false;
        }
    }

    if (all_pass) cout << "All tests passed.\n";
    else cout << "Some tests failed.\n";

    return all_pass ? 0 : 1;
}