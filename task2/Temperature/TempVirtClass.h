#pragma once

#include <cmath>

class TempVirtClass {
public:
    double temp = 0.0;

    TempVirtClass() = default;

    virtual double getTemperature(const size_t& i) = 0;

    void set_temp(const double& t) {
        temp = t;
    }

    virtual ~TempVirtClass() = default;
};
