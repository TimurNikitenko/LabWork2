PROJECT = game
LIBPROJECT = $(PROJECT).a
TESTPROJECT = test

CXX = g++
AR = ar
ARFLAGS = rsv

CXXFLAGS = -I. -std=c++17 -Wall -Wextra -g -pthread
LDXXFLAGS = $(CXXFLAGS) -L.
LDGTESTFLAGS = -lgtest -lgtest_main -lpthread

# All source files
SOURCES = main.cpp game.cpp player.cpp deck.cpp creature.cpp spell.cpp trap.cpp \
          input_handler.cpp basilisk.cpp dragon.cpp fairy.cpp golem.cpp griffin.cpp \
          phoenix.cpp shadow_mage.cpp siren.cpp troll.cpp wizard.cpp


TEST_LIB_SOURCES = game.cpp player.cpp deck.cpp creature.cpp spell.cpp trap.cpp \
                   input_handler.cpp basilisk.cpp dragon.cpp fairy.cpp golem.cpp griffin.cpp \
                   phoenix.cpp shadow_mage.cpp siren.cpp troll.cpp wizard.cpp

# Object files
OBJ = $(SOURCES:.cpp=.o)
TEST_LIB_OBJ = $(TEST_LIB_SOURCES:.cpp=.o)
TEST_SOURCES = tests/test_card.cpp tests/test_player.cpp tests/test_creature_abilities.cpp tests/test_game_logic.cpp
TEST_OBJ = tests/test_card.o tests/test_player.o tests/test_creature_abilities.o tests/test_game_logic.o

# Dependencies (all header files)
DEPS = $(wildcard *.hpp *.h)

.PHONY: all build-tests run-tests clean cleanall test

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(LDXXFLAGS)

all: $(PROJECT) $(TESTPROJECT)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(LIBPROJECT): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(TESTPROJECT): $(TEST_OBJ) $(TEST_LIB_OBJ)
	$(CXX) -o $@ $(TEST_OBJ) $(TEST_LIB_OBJ) $(LDXXFLAGS) $(LDGTESTFLAGS)

test: $(TEST_OBJ) $(TEST_LIB_OBJ)
	$(CXX) -o $(TESTPROJECT) $(TEST_OBJ) $(TEST_LIB_OBJ) $(LDXXFLAGS) $(LDGTESTFLAGS)
	./$(TESTPROJECT) --gtest_color=yes

run-tests: test

clean:
	rm -f *.o tests/*.o

cleanall: clean
	rm -f $(LIBPROJECT) $(TESTPROJECT) $(PROJECT)