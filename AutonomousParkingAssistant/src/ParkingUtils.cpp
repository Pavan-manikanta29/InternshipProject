#include "../include/ParkingUtils.h"
#include <iostream>
#include <limits>
#include <vector>

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0) {
            return value;
        }
        std::cout << "Invalid input. Please enter a non-negative number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string checkSafety(const SensorData& s) {
    // Check for collision (any sensor <= 0.1)
    if (s.left <= 0.1 || s.center <= 0.1 || s.right <= 0.1) {
        return "COLLISION! STOP IMMEDIATELY 🚨";
    }
    
    // Check if too close (any sensor < 0.3)
    if (s.left < 0.3 || s.center < 0.3 || s.right < 0.3) {
        return "TOO CLOSE! Adjust carefully ⚠️";
    }
    
    // Check if perfectly parked (all sensors between 0.3-0.5 inclusive)
    if (s.left >= 0.3 && s.left <= 0.5 && 
        s.center >= 0.3 && s.center <= 0.5 && 
        s.right >= 0.3 && s.right <= 0.5) {
        return "Perfectly Parked ✅";
    }
    
    // Otherwise safe
    return "SAFE";
}

double requiredSpace(bool parallel, double carLength, double carWidth) {
    if (parallel) {
        return carLength + 1.0;  // Parallel parking requires car length + 1.0m
    } else {
        return carWidth + 0.5;   // Perpendicular parking requires car width + 0.5m
    }
}

bool findParkingSpace(bool parallel, double carLength, double carWidth) {
    double required = requiredSpace(parallel, carLength, carWidth);
    
    std::cout << "\n=== Parking Space Scanner ===\n";
    std::cout << "Required space: " << required << " meters\n";
    
    int numSpaces;
    while (true) {
        std::cout << "Enter number of available parking spaces: ";
        if (std::cin >> numSpaces && numSpaces > 0) {
            break;
        }
        std::cout << "Invalid input. Please enter a positive integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    for (int i = 1; i <= numSpaces; i++) {
        double spaceSize = getDoubleInput("Enter size of space " + std::to_string(i) + " (meters): ");
        
        if (spaceSize >= required) {
            std::cout << "✅ Space found! Space " << i << " is suitable.\n";
            return true;
        }
    }
    
    std::cout << "🚫 No suitable parking space found.\n";
    return false;
}

void parkingAssistantLoop(bool reverseMode, bool parallel) {
    std::cout << "\n=== Parking Assistant Active ===\n";
    std::cout << "Mode: " << (reverseMode ? "REVERSE" : "FORWARD") << " | Type: " << (parallel ? "PARALLEL" : "PERPENDICULAR") << "\n\n";
    
    while (true) {
        // Get sensor readings
        std::cout << "Enter sensor readings:\n";
        double left = getDoubleInput("Left sensor (m): ");
        double center = getDoubleInput("Center sensor (m): ");
        double right = getDoubleInput("Right sensor (m): ");
        
        SensorData sensors = {left, center, right};
        std::string safetyStatus = checkSafety(sensors);
        
        std::cout << "\nStatus: " << safetyStatus << "\n";
        
        // Check for collision or perfect parking
        if (safetyStatus == "COLLISION! STOP IMMEDIATELY 🚨") {
            std::cout << "Emergency stop activated!\n";
            break;
        }
        
        if (safetyStatus == "Perfectly Parked ✅") {
            std::cout << "Parking completed successfully!\n";
            break;
        }
        
        // Provide steering and movement suggestions
        std::cout << "\n--- Guidance ---\n";
        
        // Steering suggestion
        if (sensors.left < sensors.right) {
            std::cout << "Steer RIGHT\n";
        } else if (sensors.right < sensors.left) {
            std::cout << "Steer LEFT\n";
        } else {
            std::cout << "Keep centered\n";
        }
        
        // Movement suggestion
        if (reverseMode) {
            std::cout << "Move BACKWARD\n";
        } else {
            std::cout << "Move FORWARD\n";
        }
        
        std::cout << "----------------\n\n";
    }
}
