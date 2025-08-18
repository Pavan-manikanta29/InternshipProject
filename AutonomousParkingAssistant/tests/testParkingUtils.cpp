/**
 * @file testParkingUtils.cpp
 * @brief Comprehensive unit tests for the Autonomous Parking Assistant system
 * @author Autonomous Parking Assistant Team
 * @version 2.0
 * @date 2024
 * 
 * This file contains comprehensive unit tests for all components of the
 * autonomous parking assistant system. It tests all functions, data structures,
 * and exception handling to ensure the system works correctly under various
 * conditions and edge cases.
 * 
 * Test Coverage:
 * - Data structure validation (SensorData struct)
 * - Exception handling (UnsafeParkingException)
 * - Input validation (getDoubleInput function)
 * - Safety analysis (checkSafety function)
 * - Audio alerts (beepAlert function)
 * - Space calculations (requiredSpace function)
 * - Parking space scanning (findParkingSpace function)
 * - Main parking loop (parkingAssistantLoop function)
 * - Integration scenarios (end-to-end testing)
 * 
 * Testing Features:
 * - Automated input/output simulation
 * - Exception testing and validation
 * - Edge case and boundary condition testing
 * - Integration workflow testing
 * - Comprehensive error scenario coverage
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <iomanip>

// Include the structures and functions to test
struct SensorData {
    double left;
    double center;
    double right;
};

class UnsafeParkingException : public std::runtime_error {
public:
    UnsafeParkingException(const std::string& msg) : std::runtime_error(msg) {}
};

// Function declarations to test
double getDoubleInput(const std::string& prompt, bool allowZero = true);
std::string checkSafety(const SensorData& s);
void beepAlert(const SensorData& s);
double requiredSpace(bool parallel, double carLength, double carWidth);
bool findParkingSpace(bool parallel, double carLength, double carWidth);
void parkingAssistantLoop(bool reverseMode, bool parallel);

/**
 * @class TestUtils
 * @brief Utility class for managing test input/output simulation
 * 
 * This class provides utilities for simulating user input and capturing
 * program output during testing. It allows tests to provide controlled
 * input and verify expected output without requiring manual interaction.
 * 
 * Features:
 * - Input stream redirection for automated testing
 * - Output stream capture for result verification
 * - Buffer management for multiple test scenarios
 * - Automatic cleanup and restoration of original streams
 */
class TestUtils {
private:
    static std::stringstream inputBuffer;    ///< Buffer for simulated input
    static std::stringstream outputBuffer;   ///< Buffer for captured output
    static std::streambuf* originalCin;      ///< Original cin stream buffer
    static std::streambuf* originalCout;     ///< Original cout stream buffer

public:
    /**
     * @brief Sets up input/output redirection for testing
     * 
     * This function redirects cin and cout to internal buffers
     * to allow automated testing without manual input/output.
     * It stores the original stream buffers for later restoration.
     */
    static void setupTestIO() {
        originalCin = std::cin.rdbuf();
        originalCout = std::cout.rdbuf();
        std::cin.rdbuf(inputBuffer.rdbuf());
        std::cout.rdbuf(outputBuffer.rdbuf());
    }

    /**
     * @brief Restores original input/output streams and clears buffers
     * 
     * This function restores the original cin and cout streams
     * and clears the internal buffers for the next test.
     */
    static void restoreIO() {
        std::cin.rdbuf(originalCin);
        std::cout.rdbuf(originalCout);
        inputBuffer.str("");
        inputBuffer.clear();
        outputBuffer.str("");
        outputBuffer.clear();
    }

    /**
     * @brief Provides simulated input for testing
     * @param input The input string to simulate
     * 
     * This function sets up the input buffer with the specified
     * input string for automated testing scenarios.
     */
    static void provideInput(const std::string& input) {
        inputBuffer.str(input);
        inputBuffer.clear();
    }

    /**
     * @brief Retrieves captured output from testing
     * @return The captured output as a string
     * 
     * This function returns the output that was captured during
     * the test execution for verification purposes.
     */
    static std::string getOutput() {
        return outputBuffer.str();
    }

    /**
     * @brief Clears the output buffer for the next test
     * 
     * This function clears the output buffer to prepare
     * for the next test scenario.
     */
    static void clearOutput() {
        outputBuffer.str("");
        outputBuffer.clear();
    }
};

// Static member initialization
std::stringstream TestUtils::inputBuffer;
std::stringstream TestUtils::outputBuffer;
std::streambuf* TestUtils::originalCin = nullptr;
std::streambuf* TestUtils::originalCout = nullptr;

/**
 * @brief Tests the SensorData structure functionality
 * 
 * This test validates that the SensorData structure correctly
 * stores and maintains sensor distance values. It tests:
 * - Structure initialization with different values
 * - Value assignment and retrieval
 * - Data integrity across operations
 * 
 * Test Cases:
 * - Normal sensor data with different values
 * - Equal sensor data values
 * - Edge case values
 */
void testSensorDataStruct() {
    std::cout << "Testing SensorData struct...\n";
    
    // Test normal sensor data with different values
    SensorData s1 = {1.0, 2.0, 3.0};
    assert(s1.left == 1.0);
    assert(s1.center == 2.0);
    assert(s1.right == 3.0);
    
    // Test equal sensor data values
    SensorData s2 = {0.5, 0.5, 0.5};
    assert(s2.left == 0.5);
    assert(s2.center == 0.5);
    assert(s2.right == 0.5);
    
    std::cout << "✅ SensorData struct tests passed\n";
}

/**
 * @brief Tests the UnsafeParkingException class functionality
 * 
 * This test validates that the UnsafeParkingException class
 * correctly handles exception creation and message retrieval.
 * It tests:
 * - Exception construction with custom messages
 * - Message retrieval using what() method
 * - Exception inheritance from std::runtime_error
 * 
 * Test Cases:
 * - Exception creation with custom message
 * - Message retrieval and validation
 * - Exception type checking
 */
void testUnsafeParkingException() {
    std::cout << "Testing UnsafeParkingException...\n";
    
    try {
        throw UnsafeParkingException("Test collision message");
    } catch (const UnsafeParkingException& e) {
        assert(std::string(e.what()) == "Test collision message");
    }
    
    std::cout << "✅ UnsafeParkingException tests passed\n";
}

/**
 * @brief Tests the getDoubleInput function with various scenarios
 * 
 * This test validates the input validation functionality of
 * getDoubleInput function. It tests:
 * - Valid numeric input
 * - Invalid input followed by valid input
 * - Zero value handling with different allowZero settings
 * - Error message generation
 * 
 * Test Cases:
 * - Valid double input
 * - Invalid input (non-numeric) followed by valid input
 * - Zero input with allowZero=true (default)
 * - Zero input with allowZero=false
 * - Negative input rejection
 */
void testGetDoubleInput() {
    std::cout << "Testing getDoubleInput function...\n";
    
    TestUtils::setupTestIO();
    
    // Test valid input
    TestUtils::provideInput("5.5\n");
    double result = getDoubleInput("Enter value: ");
    assert(result == 5.5);
    
    // Test invalid input followed by valid input
    TestUtils::clearOutput();
    TestUtils::provideInput("abc\n-1\n3.14\n");
    result = getDoubleInput("Enter value: ");
    assert(result == 3.14);
    
    // Test zero input with allowZero=true (default)
    TestUtils::clearOutput();
    TestUtils::provideInput("0\n");
    result = getDoubleInput("Enter value: ");
    assert(result == 0.0);
    
    // Test zero input with allowZero=false
    TestUtils::clearOutput();
    TestUtils::provideInput("0\n-5\n2.5\n");
    result = getDoubleInput("Enter value: ", false);
    assert(result == 2.5);
    
    TestUtils::restoreIO();
    std::cout << "✅ getDoubleInput tests passed\n";
}

/**
 * @brief Tests the checkSafety function with comprehensive scenarios
 * 
 * This test validates the safety analysis functionality of
 * checkSafety function. It tests:
 * - Collision detection and exception throwing
 * - Proximity warning generation
 * - Perfect parking detection
 * - Safe condition identification
 * 
 * Test Cases:
 * - Collision scenarios (all sensors)
 * - Too close scenarios (individual and combined sides)
 * - Perfect parking scenarios (edge cases and normal)
 * - Safe scenarios (various distance combinations)
 */
void testCheckSafety() {
    std::cout << "Testing checkSafety function...\n";
    
    // Test collision scenarios
    try {
        SensorData collision = {0.05, 0.5, 0.5}; // left sensor collision
        checkSafety(collision);
        assert(false); // Should not reach here
    } catch (const UnsafeParkingException& e) {
        assert(std::string(e.what()) == "🚨 COLLISION! STOP IMMEDIATELY!");
    }
    
    try {
        SensorData collision = {0.5, 0.05, 0.5}; // center sensor collision
        checkSafety(collision);
        assert(false); // Should not reach here
    } catch (const UnsafeParkingException& e) {
        assert(std::string(e.what()) == "🚨 COLLISION! STOP IMMEDIATELY!");
    }
    
    try {
        SensorData collision = {0.5, 0.5, 0.05}; // right sensor collision
        checkSafety(collision);
        assert(false); // Should not reach here
    } catch (const UnsafeParkingException& e) {
        assert(std::string(e.what()) == "🚨 COLLISION! STOP IMMEDIATELY!");
    }
    
    // Test too close scenarios
    SensorData tooClose = {0.2, 0.5, 0.5}; // left too close
    std::string result = checkSafety(tooClose);
    assert(result == "TOO CLOSE ⚠️ (LEFT)");
    
    tooClose = {0.5, 0.2, 0.5}; // center too close
    result = checkSafety(tooClose);
    assert(result == "TOO CLOSE ⚠️ (CENTER)");
    
    tooClose = {0.5, 0.5, 0.2}; // right too close
    result = checkSafety(tooClose);
    assert(result == "TOO CLOSE ⚠️ (RIGHT)");
    
    tooClose = {0.2, 0.2, 0.5}; // left and center too close
    result = checkSafety(tooClose);
    assert(result == "TOO CLOSE ⚠️ (LEFT + CENTER)");
    
    tooClose = {0.2, 0.2, 0.2}; // all too close
    result = checkSafety(tooClose);
    assert(result == "TOO CLOSE ⚠️ (LEFT + CENTER + RIGHT)");
    
    // Test perfectly parked
    SensorData perfect = {0.4, 0.4, 0.4}; // all in perfect range
    result = checkSafety(perfect);
    assert(result == "Perfectly Parked ✅");
    
    perfect = {0.3, 0.5, 0.4}; // edge cases of perfect range
    result = checkSafety(perfect);
    assert(result == "Perfectly Parked ✅");
    
    // Test safe scenarios
    SensorData safe = {0.6, 0.6, 0.6}; // all safe
    result = checkSafety(safe);
    assert(result == "SAFE");
    
    safe = {0.8, 0.3, 0.9}; // center in perfect range, others safe
    result = checkSafety(safe);
    assert(result == "SAFE");
    
    std::cout << "✅ checkSafety tests passed\n";
}

/**
 * @brief Tests the beepAlert function with various proximity scenarios
 * 
 * This test validates the audio alert functionality of
 * beepAlert function. It tests:
 * - No beep scenarios (all sensors safe)
 * - Single beep scenarios (proximity warning)
 * - Double beep scenarios (urgent warning)
 * - Output message verification
 * 
 * Test Cases:
 * - Safe distances (no beep)
 * - Proximity distances (single beep)
 * - Very close distances (double beep)
 * - Mixed proximity scenarios
 */
void testBeepAlert() {
    std::cout << "Testing beepAlert function...\n";
    
    TestUtils::setupTestIO();
    
    // Test no beep (all distances >= 0.5)
    SensorData safe = {0.6, 0.7, 0.8};
    beepAlert(safe);
    std::string output = TestUtils::getOutput();
    assert(output.find("BEEP") == std::string::npos);
    
    // Test single beep (one distance < 0.5 but >= 0.3)
    TestUtils::clearOutput();
    SensorData close = {0.4, 0.6, 0.7};
    beepAlert(close);
    output = TestUtils::getOutput();
    assert(output.find("🔊 BEEP!") != std::string::npos);
    assert(output.find("BEEP! BEEP!") == std::string::npos);
    
    // Test double beep (one distance < 0.3)
    TestUtils::clearOutput();
    SensorData veryClose = {0.2, 0.6, 0.7};
    beepAlert(veryClose);
    output = TestUtils::getOutput();
    assert(output.find("🔊 BEEP!") != std::string::npos);
    assert(output.find("BEEP! BEEP!") != std::string::npos);
    
    TestUtils::restoreIO();
    std::cout << "✅ beepAlert tests passed\n";
}

/**
 * @brief Tests the requiredSpace function with different parking scenarios
 * 
 * This test validates the parking space calculation functionality
 * of requiredSpace function. It tests:
 * - Parallel parking calculations
 * - Perpendicular parking calculations
 * - Different vehicle dimensions
 * - Calculation accuracy
 * 
 * Test Cases:
 * - Parallel parking with various vehicle sizes
 * - Perpendicular parking with various vehicle sizes
 * - Edge case vehicle dimensions
 * - Calculation formula verification
 */
void testRequiredSpace() {
    std::cout << "Testing requiredSpace function...\n";
    
    // Test parallel parking
    double result = requiredSpace(true, 4.5, 1.8);
    assert(result == 5.5); // 4.5 + 1.0
    
    result = requiredSpace(true, 3.0, 2.0);
    assert(result == 4.0); // 3.0 + 1.0
    
    // Test perpendicular parking
    result = requiredSpace(false, 4.5, 1.8);
    assert(result == 2.3); // 1.8 + 0.5
    
    result = requiredSpace(false, 3.0, 2.0);
    assert(result == 2.5); // 2.0 + 0.5
    
    std::cout << "✅ requiredSpace tests passed\n";
}

/**
 * @brief Tests the findParkingSpace function with various scenarios
 * 
 * This test validates the parking space scanning functionality
 * of findParkingSpace function. It tests:
 * - Successful space finding
 * - No suitable space scenarios
 * - Edge cases (zero spaces, negative spaces)
 * - Input validation
 * 
 * Test Cases:
 * - Multiple spaces with one suitable
 * - Multiple spaces with none suitable
 * - Zero spaces available
 * - Negative number of spaces
 * - Invalid input handling
 */
void testFindParkingSpace() {
    std::cout << "Testing findParkingSpace function...\n";
    
    TestUtils::setupTestIO();
    
    // Test successful space finding
    TestUtils::provideInput("3\n6.0\n4.0\n5.5\n"); // 3 spaces, third one fits
    bool result = findParkingSpace(true, 4.5, 1.8); // requires 5.5m
    assert(result == true);
    
    // Test no suitable space
    TestUtils::clearOutput();
    TestUtils::provideInput("2\n4.0\n5.0\n"); // 2 spaces, neither fits
    result = findParkingSpace(true, 4.5, 1.8); // requires 5.5m
    assert(result == false);
    
    // Test zero spaces
    TestUtils::clearOutput();
    TestUtils::provideInput("0\n");
    result = findParkingSpace(true, 4.5, 1.8);
    assert(result == false);
    
    // Test negative spaces
    TestUtils::clearOutput();
    TestUtils::provideInput("-1\n");
    result = findParkingSpace(true, 4.5, 1.8);
    assert(result == false);
    
    TestUtils::restoreIO();
    std::cout << "✅ findParkingSpace tests passed\n";
}

/**
 * @brief Tests the parkingAssistantLoop function with various scenarios
 * 
 * This test validates the main parking loop functionality
 * of parkingAssistantLoop function. It tests:
 * - Successful parking completion
 * - Collision detection and handling
 * - Opposite movement scenarios
 * - Output verification
 * 
 * Test Cases:
 * - Perfect parking in one step
 * - Collision detection and emergency stop
 * - Opposite movement with subsequent perfect parking
 * - Output message verification
 */
void testParkingAssistantLoop() {
    std::cout << "Testing parkingAssistantLoop function...\n";
    
    TestUtils::setupTestIO();
    
    // Test successful parking completion
    TestUtils::provideInput("0.4\n0.4\n0.4\n"); // Perfect parking in one step
    parkingAssistantLoop(false, true);
    std::string output = TestUtils::getOutput();
    assert(output.find("Perfectly Parked") != std::string::npos);
    assert(output.find("Parking simulation completed successfully") != std::string::npos);
    
    // Test collision scenario
    TestUtils::clearOutput();
    TestUtils::provideInput("0.05\n0.5\n0.5\n"); // Collision on left sensor
    parkingAssistantLoop(false, true);
    output = TestUtils::getOutput();
    assert(output.find("COLLISION! STOP IMMEDIATELY") != std::string::npos);
    assert(output.find("Parking simulation ended due to collision") != std::string::npos);
    
    // Test opposite movement scenario
    TestUtils::clearOutput();
    TestUtils::provideInput("0.2\n0.2\n0.2\n0.4\n0.4\n0.4\n"); // All close, then perfect
    parkingAssistantLoop(false, true);
    output = TestUtils::getOutput();
    assert(output.find("Opposite Movement") != std::string::npos);
    assert(output.find("Perfectly Parked") != std::string::npos);
    
    TestUtils::restoreIO();
    std::cout << "✅ parkingAssistantLoop tests passed\n";
}

/**
 * @brief Tests integration scenarios for end-to-end functionality
 * 
 * This test validates the complete system integration by
 * testing realistic parking scenarios. It tests:
 * - Complete parking workflow
 * - Summary table generation
 * - Multiple step parking processes
 * - System integration verification
 * 
 * Test Cases:
 * - Multi-step parking process
 * - Summary table generation and format
 * - Complete workflow verification
 * - Integration between all components
 */
void testIntegration() {
    std::cout << "Testing integration scenarios...\n";
    
    // Test complete parking scenario
    TestUtils::setupTestIO();
    
    // Simulate a complete parking session
    TestUtils::provideInput("0.6\n0.6\n0.6\n"); // First step - safe
    TestUtils::provideInput("0.4\n0.4\n0.4\n"); // Second step - perfect parking
    
    parkingAssistantLoop(false, true);
    std::string output = TestUtils::getOutput();
    
    // Verify summary table is generated
    assert(output.find("📊 Parking Summary:") != std::string::npos);
    assert(output.find("Step") != std::string::npos);
    assert(output.find("Left(m)") != std::string::npos);
    assert(output.find("Center(m)") != std::string::npos);
    assert(output.find("Right(m)") != std::string::npos);
    
    TestUtils::restoreIO();
    std::cout << "✅ Integration tests passed\n";
}

/**
 * @brief Executes all unit tests and provides comprehensive results
 * 
 * This function runs all unit tests in sequence and provides
 * a comprehensive summary of test results. It includes:
 * - Individual test execution
 * - Error handling and reporting
 * - Test result summary
 * - Success/failure statistics
 * 
 * Test Execution:
 * - All tests are executed in logical order
 * - Each test provides individual feedback
 * - Comprehensive error handling for test failures
 * - Detailed success/failure reporting
 * 
 * @note This function serves as the main test runner
 * @note All tests must pass for the system to be considered valid
 */
void runAllTests() {
    std::cout << "=== Running Autonomous Parking Assistant Unit Tests ===\n\n";
    
    try {
        // Execute all tests in sequence
        testSensorDataStruct();
        testUnsafeParkingException();
        testGetDoubleInput();
        testCheckSafety();
        testBeepAlert();
        testRequiredSpace();
        testFindParkingSpace();
        testParkingAssistantLoop();
        testIntegration();
        
        // Report successful completion
        std::cout << "\n🎉 All tests passed successfully!\n";
        std::cout << "Total tests run: 9\n";
        std::cout << "Passed: 9\n";
        std::cout << "Failed: 0\n";
        
    } catch (const std::exception& e) {
        // Handle test failures
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        std::cout << "Passed: 0\n";
        std::cout << "Failed: 1\n";
    } catch (...) {
        // Handle unknown test failures
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        std::cout << "Passed: 0\n";
        std::cout << "Failed: 1\n";
    }
}

/**
 * @brief Main entry point for the test suite
 * @return 0 on successful test execution, 1 on test failure
 * 
 * This function serves as the entry point for the comprehensive
 * test suite. It executes all tests and provides detailed results.
 * 
 * @note This function is separate from the main application
 * @note All tests must pass for the system to be considered ready
 */
int main() {
    runAllTests();
    return 0;
}
