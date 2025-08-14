#include "../include/ParkingUtils.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

// ---------- Input Validation ----------
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

// ---------- Safety Check ----------
string checkSafety(const SensorData& s) {
    if (s.center <= 0.1 || s.left <= 0.1 || s.right <= 0.1)
        throw UnsafeParkingException("🚨 COLLISION! STOP IMMEDIATELY!");

    vector<string> closeSides;
    if (s.left < 0.3) closeSides.push_back("LEFT");
    if (s.center < 0.3) closeSides.push_back("CENTER");
    if (s.right < 0.3) closeSides.push_back("RIGHT");

    if (!closeSides.empty()) {
        string sideList;
        for (size_t i = 0; i < closeSides.size(); ++i) {
            sideList += closeSides[i];
            if (i != closeSides.size() - 1) sideList += " + ";
        }
        return "TOO CLOSE ⚠️ (" + sideList + ")";
    }

    if (s.center >= 0.3 && s.center <= 0.5 &&
        s.left >= 0.3 && s.left <= 0.5 &&
        s.right >= 0.3 && s.right <= 0.5)
        return "Perfectly Parked ✅";

    return "SAFE";
}

// ---------- Beep for Proximity ----------
void beepAlert(const SensorData& s) {
    if (s.center < 0.5 || s.left < 0.5 || s.right < 0.5) {
        cout << "🔊 BEEP! ";
        if (s.center < 0.3 || s.left < 0.3 || s.right < 0.3) cout << "BEEP! ";
        cout << "\n";
    }
}

// ---------- Parking Space Requirement ----------
double requiredSpace(bool parallel, double carLength, double carWidth) {
    return parallel ? carLength + 1.0 : carWidth + 0.5;
}

// ---------- Scan Parking Spaces ----------
bool findParkingSpace(bool parallel, double carLength, double carWidth) {
    int numSpaces;
    cout << "\nEnter number of parking spaces to scan: ";
    while (!(cin >> numSpaces)) {
        cout << "❌ Enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (numSpaces == 0) {
        cout << "🚫 Parking space not available. Please wait for some time.\n";
        return false; // Exit program gracefully
    }
    if (numSpaces < 0) {
        cout << "❌ Number of spaces cannot be negative.\n";
        return false;
    }

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

// ---------- Parking Assistant Loop ----------
void parkingAssistantLoop(bool reverseMode, bool parallel) {
    vector<SensorData> history;
    vector<string> statusHistory;

    cout << "\n=== Parking Process Started ===\n";
    cout << "Rules:\n";
    cout << "  • Collision <= 0.10 m (STOP immediately)\n";
    cout << "  • Danger    <= 0.50 m (adjust carefully)\n";
    cout << "  • Perfect park when all distances are 0.3 - 0.5 m\n";

    int step = 0;
    bool collisionOccurred = false; // Flag to track collision

    while (true) {
        SensorData s;
        s.left   = getDoubleInput("Enter LEFT sensor distance (m): ");
        s.center = getDoubleInput(reverseMode ? "Enter REAR sensor distance (m): " : "Enter FRONT sensor distance (m): ");
        s.right  = getDoubleInput("Enter RIGHT sensor distance (m): ");

        step++;
        beepAlert(s);

        // If all sides close (<0.3 m) → opposite movement
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
            continue;
        }

        try {
            string status = checkSafety(s);
            cout << "Status: " << status << "\n";
            history.push_back(s);
            statusHistory.push_back(status);

            if (status.find("Perfectly Parked") != string::npos)
                break;

            // Steering Suggestion
            if (s.left < s.right) cout << "Left side closer → Steer RIGHT.\n";
            else if (s.right < s.left) cout << "Right side closer → Steer LEFT.\n";
            else cout << "Both sides equal → Keep centered.\n";

            // Movement Suggestion
            if (reverseMode) cout << "Move BACKWARD.\n";
            else cout << "Move FORWARD.\n";

        } catch (const UnsafeParkingException& e) {
            cout << e.what() << "\n";
            history.push_back(s);
            statusHistory.push_back("COLLISION!");
            collisionOccurred = true;
            break; // Stop the loop immediately on collision
        }

        cout << "----------------------------------------\n";
    }

    // Summary Table
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

    if (collisionOccurred)
        cout << "\n⚠️ Parking simulation ended due to collision.\n";
    else
        cout << "\n🏁 Parking simulation completed successfully.\n";
}
