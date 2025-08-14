# Autonomous Parking Assistant

A C++ console application that simulates an autonomous parking assistant system. The application helps users park their vehicles by providing real-time guidance based on sensor data.

## Features

- **Sensor Data Processing**: Handles distance measurements from three sensors (left, center, right)
- **Safety Monitoring**: Real-time collision detection and safety warnings
- **Parking Space Scanner**: Finds suitable parking spaces based on vehicle dimensions
- **Guided Parking**: Provides steering and movement instructions during parking
- **Multiple Parking Types**: Supports both parallel and perpendicular parking
- **Bidirectional Movement**: Works with both forward and reverse driving modes

## Project Structure

```
AutonomousParkingAssistant/
├── include/
│   ├── SensorData.h          // Defines struct SensorData
│   ├── ParkingUtils.h        // Declares all utility functions
├── src/
│   ├── SensorData.cpp        // (Optional) If SensorData ever has methods
│   ├── ParkingUtils.cpp      // Implements utility functions
│   ├── ParkingAssistant.cpp  // Contains parkingAssistantLoop() and related logic
│   └── main.cpp              // Entry point
├── tests/
│   ├── testParkingUtils.cpp  // Unit tests for ParkingUtils and ParkingAssistant
├── CMakeLists.txt            // Build config
└── README.md                 // Project overview
```

## Building the Project

### Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++11 support (GCC, Clang, or MSVC)

### Build Instructions

#### Option 1: Using CMake (Recommended)

1. **Create build directory:**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure with CMake:**
   ```bash
   cmake ..
   ```

3. **Build the project:**
   ```bash
   make
   ```
   (On Windows with MSVC, use `cmake --build .` instead of `make`)

4. **Run the application:**
   ```bash
   ./bin/AutonomousParkingAssistant
   ```

5. **Run unit tests:**
   ```bash
   ./bin/testParkingUtils
   ```

#### Option 2: Direct Compilation (No CMake Required)

**On Windows:**
```cmd
build.bat
```

**On Unix/Linux/macOS:**
```bash
chmod +x build.sh
./build.sh
```

Then run:
```bash
./bin/AutonomousParkingAssistant
./bin/testParkingUtils
```

## Usage

1. **Start the application** and follow the prompts
2. **Enter vehicle dimensions** (length and width in meters)
3. **Select parking type** (Parallel or Perpendicular)
4. **Choose driving mode** (Forward or Reverse)
5. **Find parking space** by entering available spaces and their sizes
6. **Follow guidance** by entering sensor readings and following the instructions

## Safety Features

- **Collision Detection**: Stops immediately if any sensor reads ≤ 0.1m
- **Proximity Warning**: Warns when any sensor reads < 0.3m
- **Perfect Parking**: Detects when all sensors are between 0.3-0.5m
- **Real-time Guidance**: Provides steering and movement suggestions

## Technical Details

- **Language**: C++11
- **Dependencies**: Standard library only (iostream, vector, limits, string)
- **Build System**: CMake
- **Testing**: Unit tests included
- **Error Handling**: Comprehensive input validation and exception handling

## Status Messages

- 🚨 **COLLISION! STOP IMMEDIATELY** - Emergency stop required
- ⚠️ **TOO CLOSE! Adjust carefully** - Proceed with caution
- ✅ **Perfectly Parked** - Parking completed successfully
- **SAFE** - Continue normal operation

## Status

✅ **Project Status: Complete and Fully Functional**

All features have been implemented and tested:
- ✅ Sensor data processing and safety monitoring
- ✅ Parking space scanning and validation
- ✅ Real-time parking guidance with steering and movement suggestions
- ✅ Support for parallel and perpendicular parking
- ✅ Forward and reverse driving modes
- ✅ Comprehensive input validation and error handling
- ✅ Unit tests with 100% pass rate
- ✅ Cross-platform build support (CMake + direct compilation)

## Contributing

This is a demonstration project. Feel free to extend the functionality or improve the code structure.
