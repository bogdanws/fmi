# Finite Automaton Project

This project implements Non-deterministic Finite Automaton (NFA) and Deterministic Finite Automaton (DFA) classes in C++. The program allows users to load an automaton from a file and check if it accepts a given string.

## Project Structure

The project has been refactored into a modular structure with the following files:

- `utils.h/cpp`: Utility functions shared across the project
- `NFA.h/cpp`: The NFA class declaration and implementation
- `DFA.h/cpp`: The DFA class (inherits from NFA) declaration and implementation
- `main.cpp`: The main program entry point
- `CMakeLists.txt`: Cross-platform build configuration

## Building the Project

To build the project using CMake:

Linux/MacOS:
```bash
./build.sh
```

Windows:
```bash
build.bat
```

This will compile all the source files and create an executable named `automaton`.

## Running the Program

To run the program:

```bash
cd build
./build/build/automaton
```

## Input File Format

The automaton file should follow this format:

```
sigma:
a
b
end
# this is a comment
states:
q0, S
q1
q2, F
end

transitions:
q0, a, q1
q1, b, q2
end
```

Where:
- `sigma:` section for the alphabet
- `states:` section for states (with S for start state, F for final states)
- `transitions:` section for transitions in the format "from_state, symbol, to_state"

## Author

Andreiana Bogdan Mihail - grupa 151 