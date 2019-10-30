#!/usr/bin/make -f
CXX=clang++
CXXFLAGS=-I. -std=c++11 -Wall -Wextra -g -ggdb -O0

BUILD_DIRECTORY = ./build
CPP = $(wildcard components/*.cpp) \
	$(wildcard mechanics/*.cpp) \
	$(wildcard objects/*.cpp) \
	$(wildcard utilities/*.cpp)

OBJ = $(CPP:%.cpp=$(BUILD_DIRECTORY)/%.o)

TEST_CPP = $(wildcard testing/unit_tests/*.cpp)
TEST_OBJ = $(TEST_CPP:%.cpp=$(BUILD_DIRECTORY)/%.o)

$(BUILD_DIRECTORY)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(BUILD_DIRECTORY)/bin/test
$(BUILD_DIRECTORY)/bin/test: testing/unit_tests/main.cpp $(OBJ) $(TEST_OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIRECTORY)/ $(OBJ)
