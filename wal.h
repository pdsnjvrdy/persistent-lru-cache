#ifndef WAL_H
#define WAL_H

#include <string>
#include <fstream>

class WALManager {
    std::ofstream file;
    std::string filepath;

public:
    WALManager(const std::string &path);
    ~WALManager();

    void append_put(int key, int value);
};

#endif