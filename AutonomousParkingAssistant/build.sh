#!/bin/bash
# build.sh
# Autonomous Parking Assistant Unix/Linux Build Script
# 
# This script compiles the Autonomous Parking Assistant project on Unix/Linux
# systems using the GCC compiler. It creates both the main application
# and the unit test suite with proper linking and optimization.
#
# Features:
# - C++14 standard compliance
# - Separate compilation of main application and tests
# - Automatic bin directory creation
# - Proper source file linking
# - Cross-platform Unix/Linux compatibility
#
# Prerequisites:
# - GCC compiler installed and in PATH
# - Unix/Linux system (Linux, macOS, BSD)
# - Bash shell environment
#
# Usage:
#   chmod +x build.sh
#   ./build.sh
#
# Output:
#   bin/AutonomousParkingAssistant - Main application
#   bin/testParkingUtils - Unit test suite
#
# Author: Autonomous Parking Assistant Team
# Version: 2.0
# Date: 2024

echo "Building Autonomous Parking Assistant..."

# Create bin directory if it doesn't exist
# Ensures the output directory exists before compilation
mkdir -p bin

# Compile main application (compile all source files together)
# Links ParkingUtils.cpp and main.cpp to create the main application executable
echo "Compiling main application..."
g++ -std=c++14 -Iinclude -o bin/AutonomousParkingAssistant src/ParkingUtils.cpp src/main.cpp

# Compile unit tests (include ParkingUtils.cpp for function implementations)
# Links testParkingUtils.cpp and ParkingUtils.cpp to create the test suite executable
echo "Compiling unit tests..."
g++ -std=c++14 -Iinclude -o bin/testParkingUtils tests/testParkingUtils.cpp src/ParkingUtils.cpp

echo "Build complete!"
echo ""
echo "To run the application: ./bin/AutonomousParkingAssistant"
echo "To run tests: ./bin/testParkingUtils"
