#!/bin/bash

# Create a build directory
mkdir -p build
cd build

# Run CMake with the BUILD_TESTS option
cmake -DBUILD_TESTS=ON ..

# Compile the project
make

# Run the tests with CTest
ctest