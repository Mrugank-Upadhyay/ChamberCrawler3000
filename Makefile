CXX=g++ 
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SRC_DIR=./src
BUILD_DIR=./build
BIN_DIR=./bin
SOURCES=$(shell find . -wholename "$(SRC_DIR)/*.cc")   # list of all .cc files in the current directory
OBJECTS=$(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)  # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=cc3k

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN_DIR)/$(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc 
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -rvf $(BUILD_DIR)/* $(BIN_DIR)/*
