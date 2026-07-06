#include "lru_cache.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int main() {
    srand(time(0));   // no getpid needed

    const string wal_file = "crash_test.wal";
    const string checkpoint_file = "crash_checkpoint.txt";

    // ----- Recovery phase -----
    LRUCache cache(1000, wal_file);

    ifstream cpin(checkpoint_file);
    vector<pair<int,int>> committed;
    int k, v;
    while (cpin >> k >> v) {
        committed.push_back({k, v});
    }
    cpin.close();

    for (auto &p : committed) {
        int val;
        if (!cache.get(p.first, val) || val != p.second) {
            cout << "FAIL: missing committed key " << p.first << endl;
            return 1;
        }
    }

    if (committed.size() >= 1000) {
        cout << "All 1000 puts already done, exiting." << endl;
        return 0;
    }

    // ----- Write phase -----
    ofstream cpout(checkpoint_file, ios::app);
    for (int i = committed.size(); i < 1000; i++) {
        int key = rand() % 1000000;
        int value = rand();
        cache.put(key, value);
        cpout << key << " " << value << "\n";
        cpout.flush();

        int check_val;
        if (!cache.get(key, check_val) || check_val != value) {
            cout << "FAIL: just-inserted key not found!" << endl;
            return 1;
        }
    }
    cpout.close();

    cout << "Completed 1000 puts without crash." << endl;
    return 0;
}