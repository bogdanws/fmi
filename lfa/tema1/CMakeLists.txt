cmake_minimum_required(VERSION 3.10)
project(automaton VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags (equivalent to those in the Makefile)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Define source files
set(SOURCES
    main.cpp
    NFA.cpp
    DFA.cpp
    utils.cpp
)

# Define the executable
add_executable(automaton ${SOURCES})

set_target_properties(automaton PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)

# Installation rules (optional)
install(TARGETS automaton DESTINATION bin)