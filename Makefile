CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: test_lru test_persistence

test_lru: test_lru.cpp lru_cache.cpp wal.cpp lru_cache.h wal.h
	$(CXX) $(CXXFLAGS) -o test_lru test_lru.cpp lru_cache.cpp wal.cpp

test_persistence: test_persistence.cpp lru_cache.cpp wal.cpp lru_cache.h wal.h
	$(CXX) $(CXXFLAGS) -o test_persistence test_persistence.cpp lru_cache.cpp wal.cpp

clean:
	rm -f test_lru test_persistence *.wal