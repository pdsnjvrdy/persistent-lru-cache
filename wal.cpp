#include "wal.h"
#include <cstdint>

WALManager::WALManager(const std::string &path) : filepath(path) {
    // Open in binary append mode
    file.open(path, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
    }
}

WALManager::~WALManager() {
    if (file.is_open())
        file.close();
}

void WALManager::append_put(int key, int value) {
    if (!file.is_open()) return;

    // opcode: 0 for PUT
    uint8_t op = 0;
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