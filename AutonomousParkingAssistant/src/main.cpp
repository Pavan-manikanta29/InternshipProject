#include "../include/ParkingUtils.h"
#include <iostream>
#include <string>
#include <limits>

int main() {
    try {
        // Welcome header
        std::cout << "========================================\n";
        std::cout << "    AUTONOMOUS PARKING ASSISTANT\n";
        std::cout << "========================================\n\n";
        
        // Get car dimensions
        double carLength = getDoubleInput("Enter car length (meters): ");
        double carWidth = getDoubleInput("Enter car width (meters): ");
        
        // Get parking type
        char parkingType;
        bool parallel;
        while (true) {
            std::cout << "Select parking type:\n";
            std::cout << "P - Parallel parking\n";
            std::cout << "T - Perpendicular parking\n";
            std::cout << "Enter choice (P/T): ";
            std::cin >> parkingType;
            
            if (parkingType == 'P' || parkingType == 'p') {
                parallel = true;
                break;
            } else if (parkingType == 'T' || parkingType == 't') {
                parallel = false;
                break;
            } else {
                std::cout << "Invalid choice. Please enter P or T.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
        // Get driving mode
        char drivingMode;
        bool reverseMode;
        while (true) {
            std::cout << "\nSelect driving mode:\n";
            std::cout << "F - Forward\n";
            std::cout << "R - Reverse\n";
            std::cout << "Enter choice (F/R): ";
            std::cin >> drivingMode;
            
            if (drivingMode == 'F' || drivingMode == 'f') {
                reverseMode = false;
                break;
            } else if (drivingMode == 'R' || drivingMode == 'r') {
                reverseMode = true;
                break;
            } else {
                std::cout << "Invalid choice. Please enter F or R.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
        // Find parking space
        if (findParkingSpace(parallel, carLength, carWidth)) {
            // Start parking assistant loop
            parkingAssistantLoop(reverseMode, parallel);
        } else {
            std::cout << "\nNo suitable parking space available. Exiting...\n";
        }
        
        std::cout << "\nThank you for using Autonomous Parking Assistant!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }
    
    return 0;
}
