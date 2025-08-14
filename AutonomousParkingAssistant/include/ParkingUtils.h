#ifndef PARKING_UTILS_H
#define PARKING_UTILS_H

#include <string>
#include "SensorData.h"

// Input validation function
double getDoubleInput(const std::string& prompt);

// Safety check function
std::string checkSafety(const SensorData& s);

// Calculate required parking space
double requiredSpace(bool parallel, double carLength, double carWidth);

// Find suitable parking space
bool findParkingSpace(bool parallel, double carLength, double carWidth);

// Parking assistant main loop
void parkingAssistantLoop(bool reverseMode, bool parallel);

#endif // PARKING_UTILS_H
