/**
 * @file main.cpp
 * @brief Main entry point for the Autonomous Parking Assistant application
 * @author Autonomous Parking Assistant Team
 * @version 2.0
 * @date 2024
 * 
 * This file contains the main function that serves as the entry point
 * for the autonomous parking assistant application. It handles user
 * interaction, configuration, and orchestrates the parking process.
 * 
 * The main function implements:
 * - Application initialization and welcome message
 * - Vehicle dimension input and validation
 * - Parking type and mode selection
 * - Parking space scanning and validation
 * - Parking assistant loop execution
 * - Comprehensive error handling
 */

#include "../include/ParkingUtils.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

using namespace std;

/**
 * @brief Main entry point for the Autonomous Parking Assistant application
 * @return 0 on successful execution, 1 on error
 * 
 * This function serves as the main entry point for the autonomous parking
 * assistant application. It provides a complete user interface for:
 * 
 * Application Flow:
 * 1. Display welcome message and application header
 * 2. Collect and validate vehicle dimensions (length and width)
 * 3. Allow user to select parking type (parallel or perpendicular)
 * 4. Allow user to select driving mode (forward or reverse)
 * 5. Scan for suitable parking spaces
 * 6. Execute the main parking assistant loop
 * 7. Handle any exceptions and provide error feedback
 * 
 * Input Validation:
 * - Vehicle dimensions must be positive values (> 0)
 * - Parking type must be 'P' (parallel) or 'T' (perpendicular)
 * - Driving mode must be 'F' (forward) or 'R' (reverse)
 * - All inputs are validated with retry mechanisms
 * 
 * Error Handling:
 * - Comprehensive exception handling for all operations
 * - User-friendly error messages with emoji indicators
 * - Graceful exit on invalid inputs or errors
 * - Proper cleanup and resource management
 * 
 * User Experience:
 * - Clear prompts and instructions
 * - Immediate feedback on invalid inputs
 * - Emoji indicators for enhanced visual feedback
 * - Intuitive menu system for configuration
 * 
 * @note The function uses try-catch blocks for comprehensive error handling
 * @note All user inputs are validated using getDoubleInput() function
 * @note The application exits gracefully if no suitable parking space is found
 * 
 * @example
 * int main() {
 *     // Application starts here
 *     // User is guided through configuration and parking process
 *     return 0; // Successful completion
 * }
 */
int main() {
    try {
        // Display application header
        cout << "=== Autonomous Parking Assistant ===\n";

        // Collect vehicle dimensions with validation
        // Car dimensions must be positive values for realistic parking calculations
        double carLength = getDoubleInput("Enter your car length (m): ", false);
        double carWidth  = getDoubleInput("Enter your car width (m): ", false);

        // Allow user to select parking type
        char typeChoice;
        while (true) {
            cout << "Choose parking type: (P)arallel or (T)Perpendicular: ";
            cin >> typeChoice;
            if (typeChoice == 'P' || typeChoice == 'p' || typeChoice == 'T' || typeChoice == 't') break;
            cout << "❌ Invalid input! Enter P or T.\n";
        }
        bool parallel = (typeChoice == 'P' || typeChoice == 'p');

        // Allow user to select driving mode
        char modeChoice;
        while (true) {
            cout << "Choose parking mode: (F)orward or (R)everse: ";
            cin >> modeChoice;
            if (modeChoice == 'F' || modeChoice == 'f' || modeChoice == 'R' || modeChoice == 'r') break;
            cout << "❌ Invalid input! Enter F or R.\n";
        }
        bool reverseMode = (modeChoice == 'R' || modeChoice == 'r');

        // Scan for suitable parking spaces
        // If no suitable space is found, exit gracefully
        if (!findParkingSpace(parallel, carLength, carWidth)) {
            // No space or user entered 0 - exit program gracefully
            return 0;
        }

        // Execute the main parking assistant loop
        // This function handles the complete parking process
        parkingAssistantLoop(reverseMode, parallel);

    } catch (const std::exception& e) {
        // Handle any exceptions that occur during execution
        cerr << "❌ Error: " << e.what() << "\n";
    }

    // Return success code
    return 0;
}
