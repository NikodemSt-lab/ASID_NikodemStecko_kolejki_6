CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

main.out: main.cpp mydeque.hpp Makefile
	$(CXX) $(CXXFLAGS) main.cpp -o $@

.PHONY: test clean

test: main.out
	./main.out

clean:
	$(RM) main.out
