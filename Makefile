PROJECT = game
LIBPROJECT = $(PROJECT).a
TESTPROJECT = test

CXX = g++
AR = ar
ARFLAGS = rsv

CXXFLAGS = -I. -std=c++17 -Wall -Wextra -g -pthread
LDXXFLAGS = $(CXXFLAGS) -L.
LDGTESTFLAGS = -lgtest -lgtest_main -lpthread

DEPS = $(wildcard *.h)
OBJ = main.o
TEST_OBJ = test.o

.PHONY: all build-tests run-tests clean cleanall

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LDXXFLAGS)

all: $(PROJECT) $(TESTPROJECT)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(LIBPROJECT): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(TESTPROJECT): $(TEST_OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(TEST_OBJ) $(LDXXFLAGS) $(LDGTESTFLAGS)

run-tests: $(TESTPROJECT)
	./$(TESTPROJECT) --gtest_color=yes

clean:
	rm -f *.o

cleanall: clean
	rm -f $(LIBPROJECT) $(TESTPROJECT) $(PROJECT)