#include "lru_cache.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    bool all_pass = true;
    const string wal_file = "persist_test.wal";
    remove(wal_file.c_str());

    // Phase 1: put some data, then destroy
    {
        LRUCache cache(3, wal_file);
        cache.put(100, 111);
        cache.put(200, 222);
        cache.put(300, 333);
    }

    // Phase 2: reopen, data should still be there
    {
        LRUCache cache(3, wal_file);
        int val;
        if (!cache.get(100, val) || val != 111) {
            cout << "FAIL: key 100 not recovered\n";
            all_pass = false;
        }
        if (!cache.get(200, val) || val != 222) {
            cout << "FAIL: key 200 not recovered\n";
            all_pass = false;
        }
        if (!cache.get(300, val) || val != 333) {
            cout << "FAIL: key 300 not recovered\n";
            all_pass = false;
        }
    }

    // Phase 3: after recovery, normal operations still work
    {
        LRUCache cache(3, wal_file);
        cache.put(400, 444);
        cache.put(500, 555);  // evictions happen, key 100 & 200 should be gone
        int val;
        if (cache.get(100, val)) {
            cout << "FAIL: key 100 should have been evicted\n";
            all_pass = false;
        }
        if (!cache.get(300, val) || val != 333) {
            cout << "FAIL: key 300 should still be there\n";
            all_pass = false;
        }
        if (!cache.get(400, val) || val != 444) {
            cout << "FAIL: key 400 should exist\n";
            all_pass = false;
        }
        if (!cache.get(500, val) || val != 555) {
            cout << "FAIL: key 500 should exist\n";
            all_pass = false;
        }
    }

    remove(wal_file.c_str());

    if (all_pass) cout << "All persistence tests passed.\n";
    else cout << "Some persistence tests failed.\n";

    return all_pass ? 0 : 1;
}