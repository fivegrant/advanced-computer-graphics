#!/usr/bin/make -f
CXX=clang++
CXXFLAGS=-I. -std=c++11 -Wall -Wextra -g -ggdb -O0

BUILD_DIRECTORY = ./build

DIRECTORIES = components mechanics objects utilities
CPP = $(wildcard components/src/*.cpp) \
	$(wildcard mechanics/src/*.cpp) \
	$(wildcard objects/src/*.cpp) \
	$(wildcard utilities/src/*.cpp)


OBJ = $(CPP:%.cpp=$(BUILD_DIRECTORY)/%.o)

TEST_CPP = $(wildcard testing/unit_tests/*.cpp)
TEST_OBJ = $(TEST_CPP:%.cpp=$(BUILD_DIRECTORY)/%.o)

$(BUILD_DIRECTORY)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(BUILD_DIRECTORY)/bin/test
$(BUILD_DIRECTORY)/bin/test: testing/main.cpp $(OBJ) $(TEST_OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

main: $(BUILD_DIRECTORY)/bin/main
$(BUILD_DIRECTORY)/bin/main: main.cpp $(OBJ)
	rm -f $(BUILD_DIRECTORY)/raytracer.hpp
	echo $(HEADERS) >> $(BUILD_DIRECTORY)/raytracer.hpp
	$(foreach d, $(DIRECTORIES), find $(d) -name *.hpp -exec echo "#include \"{}\"" >> $(BUILD_DIRECTORY)/raytracer.hpp \;;)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean entire try run refresh
clean:
	rm -rf $(BUILD_DIRECTORY)/ $(OBJ)

entire: test main

try: $(BUILD_DIRECTORY)/bin/test
	@$^
run: $(BUILD_DIRECTORY)/bin/main
	@$^

refresh: clean entire

