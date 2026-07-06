#ifndef WAL_H
#define WAL_H

#include <string>
#include <fstream>
#include <vector>
#include <utility>

class WALManager {
    std::ofstream file;
    std::string filepath;

public:
    WALManager(const std::string &path);
    ~WALManager();

    void append_put(int key, int value);
    static std::vector<std::pair<int, int>> recover_from_file(const std::string &path);
};

#endif