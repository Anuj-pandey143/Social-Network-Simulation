#!/bin/bash

# This script compiles the SocialNet Simulator project.
# It uses g++ and enables C++17 for modern features.
# -Wall enables all common warnings.

echo "Starting compilation..."

g++ -std=c++17 -Wall main.cpp -o anuj

echo "Compilation complete. Executable named 'anuj' created."
echo "To run your program, type: ./anuj"