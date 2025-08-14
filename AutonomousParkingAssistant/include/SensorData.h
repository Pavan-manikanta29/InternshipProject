#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

// SensorData struct to hold distance measurements from three sensors
struct SensorData {
    double left;    // Distance from left sensor (in meters)
    double center;  // Distance from center sensor (in meters)
    double right;   // Distance from right sensor (in meters)
};

#endif // SENSOR_DATA_H
