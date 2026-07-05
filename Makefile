CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: test_lru

test_lru: test_lru.cpp lru_cache.cpp lru_cache.h
	$(CXX) $(CXXFLAGS) -o test_lru test_lru.cpp lru_cache.cpp

clean:
	rm -f test_lru