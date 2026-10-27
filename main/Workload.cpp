#include "Workload.h"
#include "Sensor.h"
#include <vector>
#include <variant>

// ===== Для vtable =====
static std::vector<Sensor*> vtable_pool;

void init_vtable_sensors() {
    vtable_pool.clear();
    vtable_pool.reserve(256);
    for (int i = 0; i < 256; i++) {
        if (i % 3 == 0) vtable_pool.push_back(new TemperatureSensor());
        else if (i % 3 == 1) vtable_pool.push_back(new GyroscopeSensor());
        else vtable_pool.push_back(new MagnetometerSensor());
    }
}

void cleanup_vtable_sensors() {
    for (int i = 0; i < (int)vtable_pool.size(); i++) {
        delete vtable_pool[i];
    }
    vtable_pool.clear();
}

int run_vtable_pass() {
    int sum = 0;
    for (int i = 0; i < (int)vtable_pool.size(); i++) {
        sum += vtable_pool[i]->read();
    }
    return sum;
}

int get_vtable_element_size() {
    return (int)sizeof(TemperatureSensor);
}

// ===== Для variant =====
using AnySensor = std::variant<VarTemperatureSensor, 
                               VarGyroscopeSensor, 
                               VarMagnetometerSensor>;

static std::vector<AnySensor> variant_pool;

struct ReadVisitor {
    int operator()(VarTemperatureSensor& s) { return s.read(); }
    int operator()(VarGyroscopeSensor& s) { return s.read(); }
    int operator()(VarMagnetometerSensor& s) { return s.read(); }
};

void init_variant_sensors() {
    variant_pool.clear();
    variant_pool.reserve(256);
    for (int i = 0; i < 256; i++) {
        if (i % 3 == 0) variant_pool.push_back(VarTemperatureSensor());
        else if (i % 3 == 1) variant_pool.push_back(VarGyroscopeSensor());
        else variant_pool.push_back(VarMagnetometerSensor());
    }
}

void cleanup_variant_sensors() {
    variant_pool.clear();
}

int run_variant_pass() {
    int sum = 0;
    for (int i = 0; i < (int)variant_pool.size(); i++) {
        sum += std::visit(ReadVisitor(), variant_pool[i]);
    }
    return sum;
}

int get_variant_element_size() {
    return (int)sizeof(AnySensor);
}