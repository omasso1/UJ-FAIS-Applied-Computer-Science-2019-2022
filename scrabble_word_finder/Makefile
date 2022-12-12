CXX := g++
CXXFLAGS := -std=c++17
CXXFLAGS += -O2 -march=native
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -fexec-charset=UTF-8
LDFLAGS :=
LDLIBS :=

.PHONY: clean default all

default: main.x


main.x: main.cpp TreeBasedDictionary.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp TreeBasedDictionary.cpp -o main.x $(LDLIBS)


clean:
	rm *.x