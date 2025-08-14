#!/bin/bash

echo "Building Autonomous Parking Assistant..."

# Create bin directory if it doesn't exist
mkdir -p bin

# Compile main application
echo "Compiling main application..."
g++ -std=c++11 -Iinclude -o bin/AutonomousParkingAssistant src/*.cpp

# Compile unit tests
echo "Compiling unit tests..."
g++ -std=c++11 -Iinclude -o bin/testParkingUtils tests/testParkingUtils.cpp src/ParkingUtils.cpp

echo "Build complete!"
echo ""
echo "To run the application: ./bin/AutonomousParkingAssistant"
echo "To run tests: ./bin/testParkingUtils"
