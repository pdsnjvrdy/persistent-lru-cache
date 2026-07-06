CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

all: test_lru test_persistence crash_test_writer

test_lru: tests/test_lru.cpp src/lru_cache.cpp src/wal.cpp include/lru_cache.h include/wal.h
	$(CXX) $(CXXFLAGS) -o test_lru tests/test_lru.cpp src/lru_cache.cpp src/wal.cpp

test_persistence: tests/test_persistence.cpp src/lru_cache.cpp src/wal.cpp include/lru_cache.h include/wal.h
	$(CXX) $(CXXFLAGS) -o test_persistence tests/test_persistence.cpp src/lru_cache.cpp src/wal.cpp

crash_test_writer: tests/crash_test_writer.cpp src/lru_cache.cpp src/wal.cpp include/lru_cache.h include/wal.h
	$(CXX) $(CXXFLAGS) -o crash_test_writer tests/crash_test_writer.cpp src/lru_cache.cpp src/wal.cpp

clean:
	rm -f test_lru test_persistence crash_test_writer *.wal crash_checkpoint.txt