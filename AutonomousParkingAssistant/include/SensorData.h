/**
 * @file SensorData.h
 * @brief Header file containing sensor data structures and exception classes
 * @author Autonomous Parking Assistant Team
 * @version 2.0
 * @date 2024
 * 
 * This file defines the core data structures used for sensor readings
 * and the custom exception class for handling unsafe parking conditions.
 */

#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <string>
#include <stdexcept>

/**
 * @struct SensorData
 * @brief Structure to store distance measurements from three parking sensors
 * 
 * This structure holds the distance readings from the left, center, and right
 * sensors mounted on the vehicle. All distances are measured in meters.
 * 
 * @var SensorData::left
 * Distance from the left sensor in meters (0.0 or greater)
 * 
 * @var SensorData::center
 * Distance from the center/front sensor in meters (0.0 or greater)
 * 
 * @var SensorData::right
 * Distance from the right sensor in meters (0.0 or greater)
 * 
 * @example
 * SensorData sensors = {0.5, 0.8, 0.6}; // Left: 0.5m, Center: 0.8m, Right: 0.6m
 */
struct SensorData {
    double left;    ///< Distance from left sensor (meters)
    double center;  ///< Distance from center sensor (meters)
    double right;   ///< Distance from right sensor (meters)
};

/**
 * @class UnsafeParkingException
 * @brief Custom exception class for collision and unsafe parking conditions
 * 
 * This exception is thrown when the parking assistant detects a collision
 * or unsafe parking condition that requires immediate action.
 * 
 * @extends std::runtime_error
 * 
 * @example
 * try {
 *     checkSafety(sensors);
 * } catch (const UnsafeParkingException& e) {
 *     std::cout << "Emergency: " << e.what() << std::endl;
 * }
 */
class UnsafeParkingException : public std::runtime_error {
public:
    /**
     * @brief Constructor for UnsafeParkingException
     * @param msg The error message describing the unsafe condition
     * 
     * Creates a new exception with the specified error message.
     * The message should clearly indicate the nature of the unsafe condition.
     */
    UnsafeParkingException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif // SENSOR_DATA_H
