#include "../include/ParkingUtils.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

using namespace std;

int main() {
    try {
        cout << "=== Autonomous Parking Assistant ===\n";

        // Car dimensions must be > 0
        double carLength = getDoubleInput("Enter your car length (m): ", false);
        double carWidth  = getDoubleInput("Enter your car width (m): ", false);

        char typeChoice;
        while (true) {
            cout << "Choose parking type: (P)arallel or (T)Perpendicular: ";
            cin >> typeChoice;
            if (typeChoice == 'P' || typeChoice == 'p' || typeChoice == 'T' || typeChoice == 't') break;
            cout << "❌ Invalid input! Enter P or T.\n";
        }
        bool parallel = (typeChoice == 'P' || typeChoice == 'p');

        char modeChoice;
        while (true) {
            cout << "Choose parking mode: (F)orward or (R)everse: ";
            cin >> modeChoice;
            if (modeChoice == 'F' || modeChoice == 'f' || modeChoice == 'R' || modeChoice == 'r') break;
            cout << "❌ Invalid input! Enter F or R.\n";
        }
        bool reverseMode = (modeChoice == 'R' || modeChoice == 'r');

        if (!findParkingSpace(parallel, carLength, carWidth)) {
            // No space or user entered 0
            return 0;
        }

        parkingAssistantLoop(reverseMode, parallel);

    } catch (const std::exception& e) {
        cerr << "❌ Error: " << e.what() << "\n";
    }

    return 0;
}
