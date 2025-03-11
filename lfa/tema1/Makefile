CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic

SRCS = main.cpp NFA.cpp DFA.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = automaton

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC) 