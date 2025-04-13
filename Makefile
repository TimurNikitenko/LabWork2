PROJECT = game

LIBPROJECT = $(PROJECT).a

TESTPROJECT = test

CXX = g++

A = ar

AFLAGS = rsv

CCXFLAGS = -I. -std=c++17 -Wall -Wextra -g -pthread

LDXXFLAGS = $(CCXFLAGS) -L. -l:$(LIBPROJECT)

LDGTESTFLAGS = $(LDXXFLAGS) -lgtest -lgtest_main -lpthread

DEPS = $(wildcard *.h)

OBJ = main.o

TEST_OBJ = test.o

.PHONY: default all build-tests run-tests clean cleanall

default: all

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CCXFLAGS)


$(LIBPROJECT): $(OBJ)
	$(A) $(AFLAGS) $@ $^


$(TESTPROJECT): $(LIBPROJECT) $(TEST_OBJ)
	$(CXX) -o $@ $(TEST_OBJ) $(LDGTESTFLAGS)


build-tests: $(TESTPROJECT)

run-tests: build-tests
	./$(TESTPROJECT)


all: $(LIBPROJECT) build-tests


clean:
	rm -f *.o


cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(TESTPROJECT)
