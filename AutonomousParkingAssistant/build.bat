@echo off
REM build.bat
REM Autonomous Parking Assistant Windows Build Script
REM 
REM This script compiles the Autonomous Parking Assistant project on Windows
REM using the MinGW-w64 GCC compiler. It creates both the main application
REM and the unit test suite with proper linking and optimization.
REM
REM Features:
REM - C++14 standard compliance
REM - Separate compilation of main application and tests
REM - Automatic bin directory creation
REM - Proper source file linking
REM - Cross-compiler compatibility
REM
REM Prerequisites:
REM - MinGW-w64 GCC compiler installed and in PATH
REM - Windows command prompt or PowerShell
REM
REM Usage:
REM   build.bat
REM
REM Output:
REM   bin/AutonomousParkingAssistant.exe - Main application
REM   bin/testParkingUtils.exe - Unit test suite
REM
REM Author: Autonomous Parking Assistant Team
REM Version: 2.0
REM Date: 2024

echo Building Autonomous Parking Assistant...

REM Create bin directory if it doesn't exist
REM Ensures the output directory exists before compilation
if not exist "bin" mkdir bin

REM Compile main application (compile all source files together)
REM Links ParkingUtils.cpp and main.cpp to create the main application executable
echo Compiling main application...
g++ -std=c++14 -Iinclude -o bin/AutonomousParkingAssistant.exe src/ParkingUtils.cpp src/main.cpp

REM Compile unit tests (include ParkingUtils.cpp for function implementations)
REM Links testParkingUtils.cpp and ParkingUtils.cpp to create the test suite executable
echo Compiling unit tests...
g++ -std=c++14 -Iinclude -o bin/testParkingUtils.exe tests/testParkingUtils.cpp src/ParkingUtils.cpp

echo Build complete!
echo.
echo To run the application: bin\AutonomousParkingAssistant.exe
echo To run tests: bin\testParkingUtils.exe
