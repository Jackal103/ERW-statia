#include "Sensor.h"

// ===== Реализация для vtable =====
int Sensor::read() { return 0; }

int TemperatureSensor::read() {
    counter++;
    return 25 + (counter & 0xFF);
}

int GyroscopeSensor::read() {
    counter++;
    return 500 + (counter & 0xFF);
}

int MagnetometerSensor::read() {
    counter++;
    return 50 + (counter & 0xFF);
}

// ===== Реализация для variant =====
int VarTemperatureSensor::read() {
    counter++;
    return 25 + (counter & 0xFF);
}

int VarGyroscopeSensor::read() {
    counter++;
    return 500 + (counter & 0xFF);
}

int VarMagnetometerSensor::read() {
    counter++;
    return 50 + (counter & 0xFF);
}