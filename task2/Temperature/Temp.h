#include "TempVirtClass.h"

class Temp1 : public TempVirtClass {
    // Bolzman
public:
    double getTemperature(const size_t& i) override {
        return temp / std::log(1 + i);
    }

    virtual ~Temp1() = default;
};

class Temp2 : public TempVirtClass {
public:
    // Cauchy
    double getTemperature(const size_t& i) override {
        return temp / (1 + i);
    }

    virtual ~Temp2() = default;
};

class Temp3 : public TempVirtClass {
public:
    // Mixed
    double getTemperature(const size_t& i) override {
        return temp * (std::log(1 + i) / (1 + i));
    }

    virtual ~Temp3() = default;
};

