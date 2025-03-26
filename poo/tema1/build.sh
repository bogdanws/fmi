#!/bin/bash
# Simple build script for the Automaton project

# Create and enter build directory
mkdir -p build
cd build

# Configure and build the project
cmake ..
cmake --build .

echo ""
echo "Build completed successfully!"
echo "The executable is located at: $(pwd)/build/automaton"
echo ""