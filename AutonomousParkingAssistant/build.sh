#!/bin/bash

echo "Building Autonomous Parking Assistant..."

# Create bin directory if it doesn't exist
mkdir -p bin

# Compile main application (compile all source files together)
echo "Compiling main application..."
g++ -std=c++14 -Iinclude -o bin/AutonomousParkingAssistant src/ParkingUtils.cpp src/main.cpp

# Compile unit tests (include ParkingUtils.cpp for function implementations)
echo "Compiling unit tests..."
g++ -std=c++14 -Iinclude -o bin/testParkingUtils tests/testParkingUtils.cpp src/ParkingUtils.cpp

echo "Build complete!"
echo ""
echo "To run the application: ./bin/AutonomousParkingAssistant"
echo "To run tests: ./bin/testParkingUtils"
