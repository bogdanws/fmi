CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic
LDFLAGS = -static-libstdc++ -static-libgcc

SRCS = main.cpp NFA.cpp DFA.cpp utils.cpp
BUILD_DIR = build
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
EXEC = $(BUILD_DIR)/automaton

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)