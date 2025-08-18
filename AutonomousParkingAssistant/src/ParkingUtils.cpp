/**
 * @file ParkingUtils.cpp
 * @brief Implementation file for parking utility functions
 * @author Autonomous Parking Assistant Team
 * @version 2.0
 * @date 2024
 * 
 * This file contains the implementation of all parking utility functions
 * declared in ParkingUtils.h. It provides the core functionality for
 * the autonomous parking assistant system.
 */

#include "../include/ParkingUtils.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

/**
 * @brief Validates and retrieves double input from user with comprehensive error handling
 * @param prompt The message to display to the user
 * @param allowZero Whether to allow zero as a valid input (default: true)
 * @return The validated double value entered by the user
 * 
 * This function implements robust input validation with the following features:
 * - Handles invalid input types (non-numeric input)
 * - Validates range based on allowZero parameter
 * - Provides clear error messages with emoji indicators
 * - Clears input buffer on invalid input
 * - Continues prompting until valid input is received
 * 
 * Error handling:
 * - Invalid input types: Clears buffer and reprompts
 * - Negative values: Always rejected
 * - Zero values: Accepted only if allowZero is true
 * 
 * @note The function uses infinite loop with break condition for valid input
 * @note Input buffer is cleared using cin.clear() and cin.ignore()
 * 
 * @example
 * double length = getDoubleInput("Enter car length (m): ", false);
 * // Prompts until positive value is entered
 * 
 * double distance = getDoubleInput("Enter sensor distance (m): ");
 * // Accepts zero or positive values
 */
double getDoubleInput(const string& prompt, bool allowZero) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && (allowZero ? value >= 0 : value > 0))
            return value;
        cout << "❌ Invalid input! ";
        if (allowZero)
            cout << "Please enter a number 0 or greater.\n";
        else
            cout << "Please enter a number greater than 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * @brief Analyzes sensor data and determines comprehensive parking safety status
 * @param s The SensorData structure containing distance readings from all sensors
 * @return A descriptive string indicating the safety status
 * @throws UnsafeParkingException when collision is detected (any sensor ≤ 0.1m)
 * 
 * This function implements a multi-level safety analysis system:
 * 
 * Safety Levels:
 * 1. COLLISION (≤ 0.1m): Throws UnsafeParkingException for immediate stop
 * 2. TOO CLOSE (< 0.3m): Returns detailed warning with affected sides
 * 3. PERFECT PARKING (0.3m - 0.5m): All sensors in optimal range
 * 4. SAFE (> 0.5m): All sensors at safe distances
 * 
 * Features:
 * - Detailed side identification for proximity warnings
 * - Combined warnings for multiple close sides
 * - Edge case handling for perfect parking boundaries
 * - Exception-based collision handling for immediate response
 * 
 * @note The function throws exceptions for collision conditions to ensure immediate handling
 * @note Proximity warnings include specific side identification (LEFT, CENTER, RIGHT)
 * 
 * @example
 * SensorData sensors = {0.2, 0.4, 0.6};
 * try {
 *     string status = checkSafety(sensors);
 *     // Returns: "TOO CLOSE ⚠️ (LEFT)"
 * } catch (const UnsafeParkingException& e) {
 *     // Handle collision emergency
 * }
 */
string checkSafety(const SensorData& s) {
    // Check for collision condition (immediate stop required)
    if (s.center <= 0.1 || s.left <= 0.1 || s.right <= 0.1)
        throw UnsafeParkingException("🚨 COLLISION! STOP IMMEDIATELY!");

    // Build list of sides that are too close
    vector<string> closeSides;
    if (s.left < 0.3) closeSides.push_back("LEFT");
    if (s.center < 0.3) closeSides.push_back("CENTER");
    if (s.right < 0.3) closeSides.push_back("RIGHT");

    // Return detailed proximity warning if any sides are too close
    if (!closeSides.empty()) {
        string sideList;
        for (size_t i = 0; i < closeSides.size(); ++i) {
            sideList += closeSides[i];
            if (i != closeSides.size() - 1) sideList += " + ";
        }
        return "TOO CLOSE ⚠️ (" + sideList + ")";
    }

    // Check for perfect parking condition (all sensors in optimal range)
    if (s.center >= 0.3 && s.center <= 0.5 &&
        s.left >= 0.3 && s.left <= 0.5 &&
        s.right >= 0.3 && s.right <= 0.5)
        return "Perfectly Parked ✅";

    // Default safe condition
    return "SAFE";
}

/**
 * @brief Provides intelligent audio feedback based on sensor proximity levels
 * @param s The SensorData structure containing distance readings
 * 
 * This function implements a two-level audio alert system that provides
 * immediate feedback to the driver about proximity without requiring
 * visual attention. The alerts use emoji indicators for enhanced visibility.
 * 
 * Alert System:
 * - Level 1 (Single Beep): Any sensor < 0.5m - Caution warning
 * - Level 2 (Double Beep): Any sensor < 0.3m - Urgent warning
 * 
 * Features:
 * - Non-intrusive audio feedback
 * - Multiple beep levels for different urgency
 * - Emoji indicators for visual enhancement
 * - Immediate response to proximity changes
 * 
 * @note The function outputs to console but could be easily modified for actual audio
 * @note Beep patterns are designed to be attention-grabbing but not alarming
 * 
 * @example
 * SensorData sensors = {0.4, 0.6, 0.8};
 * beepAlert(sensors); // Outputs: "🔊 BEEP!"
 * 
 * SensorData sensors2 = {0.2, 0.6, 0.8};
 * beepAlert(sensors2); // Outputs: "🔊 BEEP! BEEP!"
 */
void beepAlert(const SensorData& s) {
    // Check if any sensor is within proximity range
    if (s.center < 0.5 || s.left < 0.5 || s.right < 0.5) {
        cout << "🔊 BEEP! ";
        // Additional urgent beep for very close objects
        if (s.center < 0.3 || s.left < 0.3 || s.right < 0.3) cout << "BEEP! ";
        cout << "\n";
    }
}

/**
 * @brief Calculates minimum parking space requirements based on parking type and vehicle dimensions
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * @param carLength The length of the vehicle in meters
 * @param carWidth The width of the vehicle in meters
 * @return The minimum required parking space in meters
 * 
 * This function implements industry-standard parking space calculations
 * that account for different parking types and vehicle dimensions.
 * 
 * Calculation Logic:
 * - Parallel Parking: Requires car length + 1.0m maneuvering space
 * - Perpendicular Parking: Requires car width + 0.5m maneuvering space
 * 
 * The additional space accounts for:
 * - Maneuvering room for entry and exit
 * - Safety margins for comfortable parking
 * - Standard parking space design guidelines
 * 
 * @note Calculations are based on typical parking space design standards
 * @note The function uses ternary operator for concise implementation
 * 
 * @example
 * double space1 = requiredSpace(true, 4.5, 1.8);   // Returns 5.5m (parallel)
 * double space2 = requiredSpace(false, 4.5, 1.8);  // Returns 2.3m (perpendicular)
 */
double requiredSpace(bool parallel, double carLength, double carWidth) {
    return parallel ? carLength + 1.0 : carWidth + 0.5;
}

/**
 * @brief Scans available parking spaces and identifies suitable options with detailed feedback
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * @param carLength The length of the vehicle in meters
 * @param carWidth The width of the vehicle in meters
 * @return true if a suitable space is found, false otherwise
 * 
 * This function implements a comprehensive parking space scanning system
 * that guides users through the process of finding suitable parking spaces.
 * 
 * Features:
 * - Validates number of spaces input
 * - Handles edge cases (zero, negative spaces)
 * - Provides detailed feedback for each space checked
 * - Uses requiredSpace() function for accurate calculations
 * - Graceful exit when no suitable space is available
 * 
 * Input Validation:
 * - Number of spaces must be a valid integer
 * - Handles zero spaces (graceful exit)
 * - Rejects negative numbers
 * - Validates individual space sizes
 * 
 * @note The function provides immediate feedback for each space checked
 * @note Uses getDoubleInput() for robust space size validation
 * 
 * @example
 * bool found = findParkingSpace(true, 4.5, 1.8);
 * // Prompts for number of spaces and their sizes
 * // Returns true if space >= 5.5m is found
 */
bool findParkingSpace(bool parallel, double carLength, double carWidth) {
    int numSpaces;
    cout << "\nEnter number of parking spaces to scan: ";
    
    // Validate number of spaces input
    while (!(cin >> numSpaces)) {
        cout << "❌ Enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Handle edge cases
    if (numSpaces == 0) {
        cout << "🚫 Parking space not available. Please wait for some time.\n";
        return false; // Exit program gracefully
    }
    if (numSpaces < 0) {
        cout << "❌ Number of spaces cannot be negative.\n";
        return false;
    }

    // Calculate required space and check each available space
    double required = requiredSpace(parallel, carLength, carWidth);
    for (int i = 1; i <= numSpaces; i++) {
        double space = getDoubleInput("Enter size of space " + to_string(i) + " (m): ");
        if (space >= required) {
            cout << "✅ Space found! (" << space << " m) is enough for your car.\n";
            return true;
        } else {
            cout << "❌ Space too small (" << space << " m), skipping...\n";
        }
    }
    return false;
}

/**
 * @brief Main parking assistant loop implementing comprehensive parking guidance system
 * @param reverseMode Whether the vehicle is in reverse mode (true) or forward mode (false)
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * 
 * This function implements the core parking assistance algorithm that provides
 * real-time guidance to users during the parking process. It combines multiple
 * safety and guidance systems into a comprehensive parking solution.
 * 
 * Core Features:
 * 1. Real-time sensor data collection and analysis
 * 2. Multi-level safety monitoring with collision detection
 * 3. Intelligent steering and movement guidance
 * 4. Audio proximity alerts with intensity levels
 * 5. Opposite movement detection for stuck situations
 * 6. Comprehensive parking history tracking
 * 7. Detailed summary reporting
 * 
 * Safety Systems:
 * - Collision detection with immediate emergency stop
 * - Proximity warnings with specific side identification
 * - Audio alerts for immediate feedback
 * - Opposite movement detection when all sensors are close
 * 
 * Guidance Systems:
 * - Context-aware sensor labels (FRONT/REAR based on mode)
 * - Intelligent steering suggestions based on side comparisons
 * - Mode-appropriate movement instructions
 * - Real-time status updates
 * 
 * Data Management:
 * - Complete parking history tracking
 * - Step-by-step status recording
 * - Formatted summary table generation
 * - Collision event tracking
 * 
 * @note The function maintains infinite loop until perfect parking or collision
 * @note All sensor readings are validated using getDoubleInput()
 * @note History is maintained in vectors for comprehensive reporting
 * 
 * @example
 * parkingAssistantLoop(false, true);  // Forward mode, parallel parking
 * // Guides user through parallel parking in forward mode
 * 
 * parkingAssistantLoop(true, false);   // Reverse mode, perpendicular parking
 * // Guides user through perpendicular parking in reverse mode
 */
void parkingAssistantLoop(bool reverseMode, bool parallel) {
    // Initialize history tracking vectors
    vector<SensorData> history;
    vector<string> statusHistory;

    // Display parking rules and guidelines
    cout << "\n=== Parking Process Started ===\n";
    cout << "Rules:\n";
    cout << "  • Collision <= 0.10 m (STOP immediately)\n";
    cout << "  • Danger    <= 0.50 m (adjust carefully)\n";
    cout << "  • Perfect park when all distances are 0.3 - 0.5 m\n";

    int step = 0;
    bool collisionOccurred = false; // Flag to track collision events

    // Main parking loop
    while (true) {
        // Collect sensor data from user
        SensorData s;
        s.left   = getDoubleInput("Enter LEFT sensor distance (m): ");
        s.center = getDoubleInput(reverseMode ? "Enter REAR sensor distance (m): " : "Enter FRONT sensor distance (m): ");
        s.right  = getDoubleInput("Enter RIGHT sensor distance (m): ");

        step++;
        beepAlert(s); // Provide audio feedback

        // Check for opposite movement condition (all sensors too close)
        if (s.left < 0.3 && s.center < 0.3 && s.right < 0.3) {
            string msg;
            if (!reverseMode) {
                msg = "Opposite Movement: FORWARD mode sensors close → Move BACKWARD";
                cout << "⚠️ " << msg << " and re-enter data.\n";
            } else {
                msg = "Opposite Movement: REVERSE mode sensors close → Move FORWARD";
                cout << "⚠️ " << msg << " and re-enter data.\n";
            }
            history.push_back(s);
            statusHistory.push_back(msg);
            continue; // Skip to next iteration for new data
        }

        // Analyze safety and provide guidance
        try {
            string status = checkSafety(s);
            cout << "Status: " << status << "\n";
            history.push_back(s);
            statusHistory.push_back(status);

            // Check for perfect parking completion
            if (status.find("Perfectly Parked") != string::npos)
                break;

            // Provide steering guidance based on side comparisons
            if (s.left < s.right) cout << "Left side closer → Steer RIGHT.\n";
            else if (s.right < s.left) cout << "Right side closer → Steer LEFT.\n";
            else cout << "Both sides equal → Keep centered.\n";

            // Provide movement guidance based on mode
            if (reverseMode) cout << "Move BACKWARD.\n";
            else cout << "Move FORWARD.\n";

        } catch (const UnsafeParkingException& e) {
            // Handle collision emergency
            cout << e.what() << "\n";
            history.push_back(s);
            statusHistory.push_back("COLLISION!");
            collisionOccurred = true;
            break; // Stop the loop immediately on collision
        }

        cout << "----------------------------------------\n";
    }

    // Generate comprehensive parking summary
    cout << "\n📊 Parking Summary:\n";
    cout << left << setw(8) << "Step" << setw(10) << "Left(m)" << setw(10) << "Center(m)" << setw(10) << "Right(m)" << "Status\n";
    cout << "-------------------------------------------------------------\n";
    for (size_t i = 0; i < history.size(); i++) {
        cout << left << setw(8) << i+1
             << setw(10) << history[i].left
             << setw(10) << history[i].center
             << setw(10) << history[i].right
             << statusHistory[i] << "\n";
    }

    // Provide final status message
    if (collisionOccurred)
        cout << "\n⚠️ Parking simulation ended due to collision.\n";
    else
        cout << "\n🏁 Parking simulation completed successfully.\n";
}
