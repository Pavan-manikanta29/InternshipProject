#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <string>
#include <stdexcept>

// Struct to store distances
struct SensorData {
    double left;
    double center;
    double right;
};

// Custom exception for collision
class UnsafeParkingException : public std::runtime_error {
public:
    UnsafeParkingException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif // SENSOR_DATA_H
