/**
 * @file ParkingUtils.h
 * @brief Header file containing parking utility function declarations
 * @author Autonomous Parking Assistant Team
 * @version 2.0
 * @date 2024
 * 
 * This file declares all the utility functions used by the autonomous
 * parking assistant system, including input validation, safety checking,
 * parking space calculations, and the main parking loop.
 */

#ifndef PARKING_UTILS_H
#define PARKING_UTILS_H

#include <string>
#include <vector>
#include "SensorData.h"

/**
 * @brief Validates and retrieves double input from user with error handling
 * @param prompt The message to display to the user
 * @param allowZero Whether to allow zero as a valid input (default: true)
 * @return The validated double value entered by the user
 * 
 * This function prompts the user for input and validates that it's a valid
 * double value. It handles invalid input gracefully by clearing the input
 * buffer and prompting again until valid input is received.
 * 
 * @note The function will continue prompting until valid input is provided
 * @note If allowZero is false, only positive values (> 0) are accepted
 * 
 * @example
 * double length = getDoubleInput("Enter car length (m): ", false);
 * double width = getDoubleInput("Enter car width (m): ", false);
 */
double getDoubleInput(const std::string& prompt, bool allowZero = true);

/**
 * @brief Analyzes sensor data and determines parking safety status
 * @param s The SensorData structure containing distance readings
 * @return A string describing the safety status
 * @throws UnsafeParkingException when collision is detected (≤ 0.1m)
 * 
 * This function evaluates the safety of the current parking position
 * based on sensor readings. It checks for collisions, proximity warnings,
 * and perfect parking conditions.
 * 
 * Safety thresholds:
 * - Collision: ≤ 0.1m (throws exception)
 * - Too Close: < 0.3m (warning)
 * - Perfect Parking: 0.3m - 0.5m (all sensors)
 * - Safe: > 0.5m (all sensors)
 * 
 * @example
 * try {
 *     std::string status = checkSafety(sensors);
 *     std::cout << "Status: " << status << std::endl;
 * } catch (const UnsafeParkingException& e) {
 *     std::cout << "EMERGENCY: " << e.what() << std::endl;
 * }
 */
std::string checkSafety(const SensorData& s);

/**
 * @brief Provides audio feedback based on sensor proximity
 * @param s The SensorData structure containing distance readings
 * 
 * This function generates audio alerts (beep sounds) based on how close
 * objects are to the vehicle. It provides immediate feedback to the driver
 * about proximity without requiring visual attention.
 * 
 * Alert levels:
 * - Single beep: Any sensor < 0.5m
 * - Double beep: Any sensor < 0.3m
 * 
 * @example
 * beepAlert(sensors); // Outputs: "🔊 BEEP!" or "🔊 BEEP! BEEP!"
 */
void beepAlert(const SensorData& s);

/**
 * @brief Calculates the minimum parking space required for a vehicle
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * @param carLength The length of the vehicle in meters
 * @param carWidth The width of the vehicle in meters
 * @return The minimum required parking space in meters
 * 
 * This function calculates the minimum parking space needed based on
 * the parking type and vehicle dimensions.
 * 
 * Space requirements:
 * - Parallel parking: carLength + 1.0m
 * - Perpendicular parking: carWidth + 0.5m
 * 
 * @example
 * double space = requiredSpace(true, 4.5, 1.8);  // Returns 5.5m
 * double space = requiredSpace(false, 4.5, 1.8); // Returns 2.3m
 */
double requiredSpace(bool parallel, double carLength, double carWidth);

/**
 * @brief Scans available parking spaces and finds a suitable one
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * @param carLength The length of the vehicle in meters
 * @param carWidth The width of the vehicle in meters
 * @return true if a suitable space is found, false otherwise
 * 
 * This function prompts the user to enter the number of available parking
 * spaces and their sizes, then checks if any space is large enough for
 * the vehicle. It provides feedback on each space checked.
 * 
 * The function handles various edge cases:
 * - Zero spaces available
 * - Negative number of spaces
 * - Spaces too small for the vehicle
 * 
 * @example
 * if (findParkingSpace(true, 4.5, 1.8)) {
 *     std::cout << "Suitable space found!" << std::endl;
 * } else {
 *     std::cout << "No suitable space available." << std::endl;
 * }
 */
bool findParkingSpace(bool parallel, double carLength, double carWidth);

/**
 * @brief Main parking assistant loop that guides the user through parking
 * @param reverseMode Whether the vehicle is in reverse mode (true) or forward mode (false)
 * @param parallel Whether the parking is parallel (true) or perpendicular (false)
 * 
 * This function implements the main parking assistance algorithm. It:
 * 1. Continuously reads sensor data from the user
 * 2. Analyzes safety conditions and provides warnings
 * 3. Gives steering and movement guidance
 * 4. Tracks parking history and provides a summary
 * 5. Handles collision detection and emergency stops
 * 6. Detects perfect parking conditions
 * 
 * The function maintains a history of all parking steps and provides
 * a detailed summary table at the end of the parking session.
 * 
 * Special features:
 * - Opposite movement detection when all sensors are too close
 * - Real-time audio alerts
 * - Context-aware sensor labels (FRONT/REAR based on mode)
 * - Comprehensive parking summary with step-by-step history
 * 
 * @example
 * parkingAssistantLoop(false, true); // Forward mode, parallel parking
 * parkingAssistantLoop(true, false);  // Reverse mode, perpendicular parking
 */
void parkingAssistantLoop(bool reverseMode, bool parallel);

#endif // PARKING_UTILS_H
