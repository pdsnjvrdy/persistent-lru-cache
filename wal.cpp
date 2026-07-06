#include "wal.h"
#include <cstdint>

WALManager::WALManager(const std::string &path) : filepath(path) {
    // Open in binary append mode
    file.open(path, std::ios::binary | std::ios::app);
}

WALManager::~WALManager() {
    if (file.is_open()) file.close();
}

void WALManager::append_put(int key, int value) {
    if (!file.is_open()) return;

    // opcode: 0 for PUT
    uint8_t op = 0; // PUT
    file.write(reinterpret_cast<const char*>(&op), sizeof(op));

    uint32_t key_len = sizeof(key);
    file.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
    file.write(reinterpret_cast<const char*>(&key), sizeof(key));

    uint32_t val_len = sizeof(value);
    file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));

    // Flush to disk so it survives crashes
    file.flush();
}

std::vector<std::pair<int, int>> WALManager::recover_from_file(const std::string &path) {
    std::vector<std::pair<int, int>> entries;
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) return entries;

    while (in.good()) {
        uint8_t op;
        in.read(reinterpret_cast<char*>(&op), sizeof(op));
        if (!in) break;

        uint32_t key_len;
        in.read(reinterpret_cast<char*>(&key_len), sizeof(key_len));
        if (!in) break;

        int key;
        in.read(reinterpret_cast<char*>(&key), sizeof(key));
        if (!in) break;

        uint32_t val_len;
        in.read(reinterpret_cast<char*>(&val_len), sizeof(val_len));
        if (!in) break;

        int value;
        in.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!in) break;

        if (op == 0) {
            entries.push_back({key, value});
        }
    }
    return entries;
}