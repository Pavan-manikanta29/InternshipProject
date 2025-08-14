cmake_minimum_required(VERSION 3.10)
project(AutonomousParkingAssistant)

# Set C++ standard to C++14 for better compatibility
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Create main executable (compile all source files together)
add_executable(AutonomousParkingAssistant src/ParkingUtils.cpp src/main.cpp)

# Create test executable (include ParkingUtils.cpp for function implementations)
add_executable(testParkingUtils tests/testParkingUtils.cpp src/ParkingUtils.cpp)

# Set output directories
set_target_properties(AutonomousParkingAssistant PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(testParkingUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Print configuration info
message(STATUS "Building Autonomous Parking Assistant")
message(STATUS "Source files: src/ParkingUtils.cpp src/main.cpp")
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
