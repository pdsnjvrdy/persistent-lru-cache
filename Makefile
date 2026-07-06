CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: test_lru test_persistence crash_test_writer

test_lru: test_lru.cpp lru_cache.cpp wal.cpp lru_cache.h wal.h
	$(CXX) $(CXXFLAGS) -o test_lru test_lru.cpp lru_cache.cpp wal.cpp

test_persistence: test_persistence.cpp lru_cache.cpp wal.cpp lru_cache.h wal.h
	$(CXX) $(CXXFLAGS) -o test_persistence test_persistence.cpp lru_cache.cpp wal.cpp

crash_test_writer: crash_test_writer.cpp lru_cache.cpp wal.cpp lru_cache.h wal.h
	$(CXX) $(CXXFLAGS) -o crash_test_writer crash_test_writer.cpp lru_cache.cpp wal.cpp

clean:
	rm -f test_lru test_persistence crash_test_writer *.wal crash_checkpoint.txt