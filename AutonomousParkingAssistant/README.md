# Autonomous Parking Assistant

A comprehensive C++ console application that simulates an advanced autonomous parking assistant system. The application provides intelligent guidance for parking vehicles with enhanced safety features, real-time monitoring, and detailed parking history.

## 🚗 Enhanced Features

- **Advanced Sensor Data Processing**: Handles distance measurements from three sensors (left, center, right) with intelligent analysis
- **Enhanced Safety Monitoring**: Real-time collision detection with custom exceptions and detailed proximity warnings
- **Smart Parking Space Scanner**: Finds suitable parking spaces with detailed feedback and validation
- **Intelligent Guided Parking**: Provides context-aware steering and movement instructions
- **Multiple Parking Types**: Supports both parallel and perpendicular parking with optimized space calculations
- **Bidirectional Movement**: Works with both forward and reverse driving modes with mode-specific guidance
- **Real-time Audio Alerts**: Beep warnings for proximity detection with intensity levels
- **Parking History & Analytics**: Detailed summary table with step-by-step parking progress
- **Opposite Movement Detection**: Automatically detects when all sensors are too close and suggests reverse movement
- **Enhanced Input Validation**: Robust error handling with user-friendly messages and retry mechanisms

## 📁 Project Structure

```
AutonomousParkingAssistant/
├── include/
│   ├── SensorData.h          // Defines SensorData struct and UnsafeParkingException
│   └── ParkingUtils.h        // Declares all utility functions
├── src/
│   ├── ParkingUtils.cpp      // Implements all parking utility functions
│   ├── ParkingAssistant.cpp  // Contains parking assistant logic
│   └── main.cpp              // Entry point with enhanced UI
├── tests/
│   └── testParkingUtils.cpp  // Comprehensive unit tests
├── bin/                      // Compiled executables
├── build/                    // CMake build files
├── CMakeLists.txt            // Build configuration
├── build.bat                 // Windows build script
├── build.sh                  // Unix/Linux build script
└── README.md                 // Project documentation
```

## 🛠️ Building the Project

### Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++14 support (GCC, Clang, or MSVC)

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

5. **Run comprehensive unit tests:**
   ```bash
   ./bin/testParkingUtils
   ```

#### Option 2: Direct Compilation

**On Windows:**
```cmd
build.bat
```

**On Unix/Linux/macOS:**
```bash
chmod +x build.sh
./build.sh
```

## 🎮 Usage Guide

### 1. Application Startup
```
=== Autonomous Parking Assistant ===
Enter your car length (m): 4.5
Enter your car width (m): 1.8
```

### 2. Parking Configuration
```
Choose parking type: (P)arallel or (T)Perpendicular: P
Choose parking mode: (F)orward or (R)everse: F
```

### 3. Parking Space Search
```
Enter number of parking spaces to scan: 3
Enter size of space 1 (m): 4.0
❌ Space too small (4.0 m), skipping...
Enter size of space 2 (m): 5.5
✅ Space found! (5.5 m) is enough for your car.
```

### 4. Real-time Parking Guidance
```
=== Parking Process Started ===
Rules:
  • Collision <= 0.10 m (STOP immediately)
  • Danger    <= 0.50 m (adjust carefully)
  • Perfect park when all distances are 0.3 - 0.5 m

Enter LEFT sensor distance (m): 0.4
Enter FRONT sensor distance (m): 0.4
Enter RIGHT sensor distance (m): 0.4
🔊 BEEP! 
Status: Perfectly Parked ✅
```

### 5. Parking Summary
```
📊 Parking Summary:
Step    Left(m)   Center(m)  Right(m)  Status
-------------------------------------------------------------
1       0.4       0.4        0.4       Perfectly Parked ✅

🏁 Parking simulation completed successfully.
```

## 🛡️ Advanced Safety Features

### Collision Detection
- **Emergency Stop**: Immediate halt when any sensor ≤ 0.1m
- **Custom Exception**: `UnsafeParkingException` for collision handling
- **Automatic Termination**: Program stops safely on collision detection

### Proximity Monitoring
- **Detailed Warnings**: Specific side identification (LEFT, CENTER, RIGHT)
- **Combined Alerts**: Multiple close sides shown as "LEFT + CENTER + RIGHT"
- **Audio Feedback**: 🔊 BEEP! alerts with intensity levels
- **Visual Indicators**: ⚠️ emojis for enhanced user experience

### Perfect Parking Detection
- **Optimal Range**: All sensors between 0.3-0.5m
- **Edge Case Handling**: Inclusive boundary conditions
- **Success Confirmation**: ✅ Perfectly Parked status

## 🔧 Technical Enhancements

### Enhanced Input Validation
- **Robust Error Handling**: Invalid input recovery with retry loops
- **User-Friendly Messages**: ❌ Clear error indicators with helpful guidance
- **Zero Value Control**: Configurable zero value acceptance
- **Type Safety**: Comprehensive input type checking

### Smart Parking Logic
- **Opposite Movement Detection**: Automatic reverse guidance when all sensors close
- **Context-Aware Prompts**: Mode-specific sensor labels (FRONT/REAR)
- **Intelligent Steering**: Left/right side comparison for optimal guidance
- **Movement Suggestions**: Mode-appropriate forward/backward instructions

### Data Management
- **Parking History**: Complete step-by-step record of parking process
- **Status Tracking**: Detailed status history for each step
- **Summary Analytics**: Formatted table with all parking data
- **Collision Tracking**: Special handling for collision scenarios

## 📊 Status Messages & Indicators

### Safety Levels
- 🚨 **COLLISION! STOP IMMEDIATELY!** - Emergency stop required
- ⚠️ **TOO CLOSE (LEFT/CENTER/RIGHT)** - Proceed with caution
- ✅ **Perfectly Parked** - Parking completed successfully
- **SAFE** - Continue normal operation

### Audio Alerts
- 🔊 **BEEP!** - Single proximity warning
- 🔊 **BEEP! BEEP!** - Double warning for very close objects

### Movement Guidance
- **Left side closer → Steer RIGHT**
- **Right side closer → Steer LEFT**
- **Both sides equal → Keep centered**
- **Move FORWARD/BACKWARD**

## 🧪 Comprehensive Testing

### Unit Test Coverage
- ✅ **SensorData Struct**: Data structure validation
- ✅ **UnsafeParkingException**: Exception handling
- ✅ **getDoubleInput**: Input validation with edge cases
- ✅ **checkSafety**: All safety scenarios (collision, proximity, perfect parking)
- ✅ **beepAlert**: Audio alert functionality
- ✅ **requiredSpace**: Space calculation for both parking types
- ✅ **findParkingSpace**: Space scanning and validation
- ✅ **parkingAssistantLoop**: Complete parking simulation
- ✅ **Integration Tests**: End-to-end functionality

### Test Features
- **Input/Output Simulation**: Automated test input and output capture
- **Exception Testing**: Comprehensive error scenario coverage
- **Edge Case Validation**: Boundary condition testing
- **Integration Verification**: Complete workflow testing

## 🚀 Performance & Compatibility

- **Language**: C++14 (enhanced from C++11)
- **Dependencies**: Standard library only
- **Build System**: CMake with cross-platform support
- **Error Handling**: Comprehensive exception handling
- **Memory Management**: Automatic resource management
- **Cross-Platform**: Windows, Linux, macOS support

## 📈 Project Status

✅ **Project Status: Enhanced and Production-Ready**

All enhanced features have been implemented and thoroughly tested:
- ✅ Advanced sensor data processing with intelligent analysis
- ✅ Enhanced safety monitoring with custom exceptions
- ✅ Smart parking space scanning with detailed feedback
- ✅ Intelligent guided parking with context-aware instructions
- ✅ Real-time audio alerts with proximity detection
- ✅ Comprehensive parking history and analytics
- ✅ Opposite movement detection and guidance
- ✅ Enhanced input validation with user-friendly error handling
- ✅ Complete unit test coverage with 100% pass rate
- ✅ Cross-platform build support with modern C++14 features

## 🤝 Contributing

This is a demonstration project showcasing advanced C++ programming concepts. Feel free to extend the functionality, improve the code structure, or add new features.

## 📝 License

This project is open source and available for educational and demonstration purposes.
