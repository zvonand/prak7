#ifndef TASK3_FUNCTION_H
#define TASK3_FUNCTION_H

#include <string>
#include <vector>
#include <cmath>
#include <memory>


class TFunction {
public:
    TFunction() = default;
    ~TFunction() = default;

    virtual double getDerivative(double x);
    virtual double getValue(double x);
    static std::shared_ptr<TFunction> Create(std::string type, double param=1);
    static std::shared_ptr<TFunction> Create(std::string type, std::vector<double> coeffVec={1});

    virtual TFunction* operator-();
};


class TIdent : public TFunction {
// f(x) = x
public:
    explicit TIdent(double param=0){}

    double getValue(double x) {
        return x;
    }
    double getDerivative(double x) {
        return 1;
    }
};

class TConst : public TFunction {
// f(x) = c
protected:
    double val;
public:
    explicit TConst(double value=0) : val(value) {};

    double getValue(double x) override {
        return val;
    }

    double getDerivative(double x) override {
        return 0;
    }
};

class TPower : public TFunction {
// f(x) = x^pow
protected:
    double power;
public:
    explicit TPower(double power=0) : power(power) {};

    double getValue(double x) override {
        return std::pow(x, power);
    }

    double getDerivative(double x) override {
        return power * std::pow(x, power-1);
    }
};

class TExp : public TFunction {
// f(x) = x^pow
public:
    explicit TExp(double param=0) {};

    double getValue(double x) override {
        return std::exp(x);
    }

    double getDerivative(double x) override {
        return std::exp(x);
    }
};

class TPolynom : public TFunction {
// f(x) = P(x)
public:
    explicit TPolynom(double param=0) {};
    double getValue(double x) {
        return x;
    }
    double getDerivative(double x) {
        return 1;
    }
};


#endif