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

// Test utilities
class TestUtils {
private:
    static std::stringstream inputBuffer;
    static std::stringstream outputBuffer;
    static std::streambuf* originalCin;
    static std::streambuf* originalCout;

public:
    static void setupTestIO() {
        originalCin = std::cin.rdbuf();
        originalCout = std::cout.rdbuf();
        std::cin.rdbuf(inputBuffer.rdbuf());
        std::cout.rdbuf(outputBuffer.rdbuf());
    }

    static void restoreIO() {
        std::cin.rdbuf(originalCin);
        std::cout.rdbuf(originalCout);
        inputBuffer.str("");
        inputBuffer.clear();
        outputBuffer.str("");
        outputBuffer.clear();
    }

    static void provideInput(const std::string& input) {
        inputBuffer.str(input);
        inputBuffer.clear();
    }

    static std::string getOutput() {
        return outputBuffer.str();
    }

    static void clearOutput() {
        outputBuffer.str("");
        outputBuffer.clear();
    }
};

std::stringstream TestUtils::inputBuffer;
std::stringstream TestUtils::outputBuffer;
std::streambuf* TestUtils::originalCin = nullptr;
std::streambuf* TestUtils::originalCout = nullptr;

// Test functions
void testSensorDataStruct() {
    std::cout << "Testing SensorData struct...\n";
    
    SensorData s1 = {1.0, 2.0, 3.0};
    assert(s1.left == 1.0);
    assert(s1.center == 2.0);
    assert(s1.right == 3.0);
    
    SensorData s2 = {0.5, 0.5, 0.5};
    assert(s2.left == 0.5);
    assert(s2.center == 0.5);
    assert(s2.right == 0.5);
    
    std::cout << "✅ SensorData struct tests passed\n";
}

void testUnsafeParkingException() {
    std::cout << "Testing UnsafeParkingException...\n";
    
    try {
        throw UnsafeParkingException("Test collision message");
    } catch (const UnsafeParkingException& e) {
        assert(std::string(e.what()) == "Test collision message");
    }
    
    std::cout << "✅ UnsafeParkingException tests passed\n";
}

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

void runAllTests() {
    std::cout << "=== Running Autonomous Parking Assistant Unit Tests ===\n\n";
    
    try {
        testSensorDataStruct();
        testUnsafeParkingException();
        testGetDoubleInput();
        testCheckSafety();
        testBeepAlert();
        testRequiredSpace();
        testFindParkingSpace();
        testParkingAssistantLoop();
        testIntegration();
        
        std::cout << "\n🎉 All tests passed successfully!\n";
        std::cout << "Total tests run: 9\n";
        std::cout << "Passed: 9\n";
        std::cout << "Failed: 0\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        std::cout << "Passed: 0\n";
        std::cout << "Failed: 1\n";
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        std::cout << "Passed: 0\n";
        std::cout << "Failed: 1\n";
    }
}

int main() {
    runAllTests();
    return 0;
}
