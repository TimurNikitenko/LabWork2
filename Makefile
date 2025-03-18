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

TEST-OBJ = tests.o

.PHONY: default

default: all

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CCXFLAGS)

$(LIBPROJECT): $(OBJ)
	$(A) $(AFLAGS) $@ $^

$(TESTPROJECT): $(LIBPROJECT) $(TEST-OBJ)
	$(CXX) -o $@ $(TEST-OBJ) $(LDGTESTFLAGS)

build-tests: $(TESTPROJECT)

run-tests: $(TESTPROJECT)
	./$(TESTPROJECT)

all: $(LIBPROJECT) build-tests

clean:
	rm -f *.o

cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(TESTPROJECT)
