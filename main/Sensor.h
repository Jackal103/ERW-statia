#pragma once

// ===== ВАРИАНТ А: с виртуальными методами (vtable) =====
class Sensor {
public:
    virtual ~Sensor() {}
    virtual int read();
protected:
    int counter = 0;
};

class TemperatureSensor : public Sensor {
public:
    int read() override;
};

class GyroscopeSensor : public Sensor {
public:
    int read() override;
};

class MagnetometerSensor : public Sensor {
public:
    int read() override;
};

// ===== ВАРИАНТ Б: без виртуальных методов (variant) =====
class VarTemperatureSensor {
public:
    int read();
private:
    int counter = 0;
};

class VarGyroscopeSensor {
public:
    int read();
private:
    int counter = 0;
};

class VarMagnetometerSensor {
public:
    int read();
private:
    int counter = 0;
};