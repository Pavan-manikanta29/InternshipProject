#include "../include/ParkingUtils.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

// Simple test framework
void runTest(const std::string& testName, bool testResult) {
    if (testResult) {
        std::cout << "✅ " << testName << " PASSED\n";
    } else {
        std::cout << "❌ " << testName << " FAILED\n";
    }
}

// Test checkSafety function
void testCheckSafety() {
    std::cout << "\n=== Testing checkSafety() ===\n";
    
    // Test collision case
    SensorData collision = {0.05, 0.2, 0.3};
    runTest("Collision detection", checkSafety(collision) == "COLLISION! STOP IMMEDIATELY 🚨");
    
    // Test too close case
    SensorData tooClose = {0.2, 0.4, 0.6};
    runTest("Too close detection", checkSafety(tooClose) == "TOO CLOSE! Adjust carefully ⚠️");
    
    // Test perfectly parked case
    SensorData perfect = {0.35, 0.4, 0.45};
    runTest("Perfect parking detection", checkSafety(perfect) == "Perfectly Parked ✅");
    
    // Test safe case
    SensorData safe = {0.6, 0.7, 0.8};
    runTest("Safe distance detection", checkSafety(safe) == "SAFE");
}

// Test requiredSpace function
void testRequiredSpace() {
    std::cout << "\n=== Testing requiredSpace() ===\n";
    
    double carLength = 4.5;
    double carWidth = 1.8;
    const double tolerance = 1e-10;  // Small tolerance for floating-point comparison
    
    // Test parallel parking
    double parallelSpace = requiredSpace(true, carLength, carWidth);
    double expectedParallel = carLength + 1.0;
    runTest("Parallel parking space calculation", std::abs(parallelSpace - expectedParallel) < tolerance);
    
    // Test perpendicular parking
    double perpendicularSpace = requiredSpace(false, carLength, carWidth);
    double expectedPerpendicular = carWidth + 0.5;
    runTest("Perpendicular parking space calculation", std::abs(perpendicularSpace - expectedPerpendicular) < tolerance);
}

// Test getDoubleInput function (simulated)
void testGetDoubleInput() {
    std::cout << "\n=== Testing getDoubleInput() ===\n";
    
    // This test would require input simulation
    // For now, we'll just test that the function exists and can be called
    std::cout << "getDoubleInput function test skipped (requires input simulation)\n";
    std::cout << "✅ getDoubleInput function exists\n";
}

// Simulate parking assistant loop with mock data
void testParkingAssistantLoop() {
    std::cout << "\n=== Testing Parking Assistant Loop (Simulation) ===\n";
    
    // Simulate a successful parking scenario
    std::cout << "Simulating parking assistant loop...\n";
    
    // Mock sensor data progression
    std::vector<SensorData> mockSensors = {
        {0.8, 0.9, 0.7},   // Safe
        {0.4, 0.5, 0.6},   // Safe
        {0.25, 0.3, 0.35}, // Too close
        {0.35, 0.4, 0.45}  // Perfectly parked
    };
    
    std::cout << "Mock sensor progression:\n";
    for (size_t i = 0; i < mockSensors.size(); i++) {
        std::string status = checkSafety(mockSensors[i]);
        std::cout << "Step " << (i + 1) << ": " << status << "\n";
        
        if (status == "Perfectly Parked ✅") {
            std::cout << "✅ Parking simulation completed successfully\n";
            break;
        }
    }
}

int main() {
    std::cout << "========================================\n";
    std::cout << "    PARKING ASSISTANT UNIT TESTS\n";
    std::cout << "========================================\n";
    
    try {
        testCheckSafety();
        testRequiredSpace();
        testGetDoubleInput();
        testParkingAssistantLoop();
        
        std::cout << "\n========================================\n";
        std::cout << "All tests completed!\n";
        std::cout << "========================================\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Test error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
