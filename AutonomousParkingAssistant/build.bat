@echo off
echo Building Autonomous Parking Assistant...

REM Create bin directory if it doesn't exist
if not exist "bin" mkdir bin

REM Compile main application (compile all source files together)
echo Compiling main application...
g++ -std=c++14 -Iinclude -o bin/AutonomousParkingAssistant.exe src/ParkingUtils.cpp src/main.cpp

REM Compile unit tests (include ParkingUtils.cpp for function implementations)
echo Compiling unit tests...
g++ -std=c++14 -Iinclude -o bin/testParkingUtils.exe tests/testParkingUtils.cpp src/ParkingUtils.cpp

echo Build complete!
echo.
echo To run the application: bin\AutonomousParkingAssistant.exe
echo To run tests: bin\testParkingUtils.exe
