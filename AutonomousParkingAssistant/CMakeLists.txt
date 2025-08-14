cmake_minimum_required(VERSION 3.10)
project(AutonomousParkingAssistant)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Find all source files in src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create main executable
add_executable(AutonomousParkingAssistant ${SOURCES})

# Create test executable
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
message(STATUS "Source files: ${SOURCES}")
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/include")
