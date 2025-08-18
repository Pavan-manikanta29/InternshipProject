# CMakeLists.txt
# Autonomous Parking Assistant Build Configuration
# 
# This file configures the build system for the Autonomous Parking Assistant
# project using CMake. It defines the project structure, compiler settings,
# and target executables for both the main application and unit tests.
#
# Features:
# - C++14 standard compliance
# - Cross-platform build support
# - Separate targets for main application and tests
# - Automated output directory configuration
# - Comprehensive build information display
#
# Usage:
#   mkdir build && cd build
#   cmake ..
#   make
#
# Author: Autonomous Parking Assistant Team
# Version: 2.0
# Date: 2024

cmake_minimum_required(VERSION 3.10)
project(AutonomousParkingAssistant)

# Set C++ standard to C++14 for better compatibility
# This enables modern C++ features while maintaining broad compiler support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
# Specifies where to find header files for the project
include_directories(include)

# Create main executable (compile all source files together)
# Links ParkingUtils.cpp and main.cpp to create the main application
add_executable(AutonomousParkingAssistant src/ParkingUtils.cpp src/main.cpp)

# Create test executable (include ParkingUtils.cpp for function implementations)
# Links testParkingUtils.cpp and ParkingUtils.cpp to create the test suite
add_executable(testParkingUtils tests/testParkingUtils.cpp src/ParkingUtils.cpp)

# Set output directories
# Configures where compiled executables will be placed
set_target_properties(AutonomousParkingAssistant PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(testParkingUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Print configuration info
# Displays build configuration information for verification
message(STATUS "Building Autonomous Parking Assistant")
message(STATUS "Source files: src/ParkingUtils.cpp src/main.cpp")
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
