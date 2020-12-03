#ifndef TASK3_FUNCTION_H
#define TASK3_FUNCTION_H

#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <initializer_list>
#include <map>
#include <boost/format.hpp>
#include <type_traits>
#include <tuple>

class TFunction {
public:
    TFunction() = default;
    ~TFunction() = default;

    virtual double getDerivative(double x) const = 0;
    virtual double getValue(double x) const = 0;
    virtual std::string toString() const = 0;
    double operator()(const double& x) const {
        return getValue(x);
    }
};

class TPower : public TFunction {
// f(x) = a * x^n
protected:
    double a, n;
public:
    TPower() = delete;
    TPower(const std::initializer_list<double>& val) {
        if (val.size() == 0) {
            a = 1; n = 0;   // there we assume that was an ident function
        } else if (val.size() == 1) {
            a = 1; n = *val.begin();
        } else if (val.size() >= 2) {
            a = *val.begin();
            n = *(val.begin()+1);
        }
    }

    std::string toString() const override  {
        if (a) {
            std::string pp = "";
            if (n == 1) {pp = "x";} else if (n > 1) {pp = str(boost::format("x^%1%") % n);}
            if (a == 1) {
                return pp == "" ? "1" : pp;
            } else {
                return str(boost::format("%1%%2%") % a % pp);
            }
        } else {
            return std::string("0");
        }
    }

    double getValue(double x) const override {
        return a * std::pow (x, n);
    }

    double getDerivative(double x) const override {
        if (n == 0) {
            return 0;
        } else {
            return n * a * std::pow(x, n - 1);
        }
    }
};

class TIdent : public TPower {
// f(x) = x
public:
    TIdent(const std::initializer_list<double>& val) : TPower({1, 1}) {};
    std::string toString() const override { return std::string("x");}
};

class TConst : public TPower {
public:
    TConst(const std::initializer_list<double>& val) : TPower({*val.begin(), 0}) {};
    std::string toString() const override {
        return std::to_string(a);
    };
};

class TExp : public TFunction {
// f(x) = a * e^(nx)
protected:
    double a, n;
public:
    TExp(const std::initializer_list<double>& val) {
        if (val.size() == 1) {
            a = 1; n = *val.begin();
        } else if (val.size() >= 2) {
            a = *val.begin(); n = *(val.begin() + 1);
        } else {
            throw std::logic_error("TExp requires at least 1 parameter");
        }
    }

    std::string toString() const override {
        if (a) {
            return a != 1 ? str(boost::format("%1%e^%2%") % a % n) : str(boost::format("e^%1%") % n);
        } else {
            return std::string("0");
        }
    }

    double getValue(double x) const override {
        return a * std::exp (n * x);
    }

    double getDerivative(double x) const override {
        return n * a * std::exp (n * x);
    }

};



double arithms(const double a, const double b, const char c) {
    switch (c) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            throw std::logic_error(std::string("Operation not supported") + std::to_string(c));
    }
}


using monomial = std::pair<char, std::shared_ptr<TFunction>>;

class TSuper : public TFunction {
// f(x) = g(x) + k(x) + ....
public:
    std::vector<monomial> monoms;

    TSuper() = default;

    TSuper(const std::vector<double>& val){
        int count = 0;
        for (double c : val) {
            monoms.push_back(std::make_pair(c>=0 ? '+' : '-',
                                            std::make_shared<TPower>(TPower({std::abs(c), static_cast<double>(count)}))));
            ++count;
        }
    }

    std::string toString() const override {
        std::string ret;
        if (monoms.size()) {
            auto ret = std::string();
            bool first = true;
            for (const auto& m : monoms) {
                if (!first) {
                    ret += m.first;
                }
                ret += std::string(" (") + m.second->toString() + ") ";
                first = false;
            }
            return ret;
        } else {
            return std::string("0");
        }
    }

    double getValue(double x) const override {
        double total = 0;
        for (const auto& m : monoms) {
            total = arithms(total, m.second->getValue(x), m.first);
        }
        return total;
    }

    double getDerivative(double x) const override {
        if (monoms.size() > 2) {
            double deriv = 0;
            double total = 0;
            for (const auto &m : monoms) {
                switch (m.first) {
                    case '+':
                        deriv += m.second->getDerivative(x);
                        total += m.second->getValue(x);
                        break;
                    case '-':
                        deriv -= m.second->getDerivative(x);
                        total -= m.second->getValue(x);
                        break;
                    case '*':
                        deriv = deriv * m.second->getDerivative(x) + total * m.second->getValue(x);
                        total *= m.second->getValue(x);
                        break;
                    case '/':
                        deriv = (deriv * m.second->getDerivative(x) - total * m.second->getValue(x)) /
                                std::pow(m.second->getValue(x), 2);
                        total /= m.second->getValue(x);
                        break;
                    default:
                        throw std::logic_error(std::string("Operation not supported") + std::to_string(m.first));
                }
            }
            return deriv;
        } else {
            switch (monoms[1].first) {
                case '+':
                    return monoms[0].second->getDerivative(x) + monoms[1].second->getDerivative(x);
                case '-':
                    return monoms[0].second->getDerivative(x) - monoms[1].second->getDerivative(x);
                case '*':
                    return monoms[0].second->getDerivative(x)*monoms[1].second->getValue(x)
                    + monoms[1].second->getDerivative(x)*monoms[0].second->getValue(x);
                case '/':
                    return (monoms[0].second->getDerivative(x)*monoms[1].second->getValue(x)
                           - monoms[1].second->getDerivative(x)*monoms[0].second->getValue(x)) /
                            std::pow(monoms[1].second->getValue(x), 2);
                default:
                    throw std::logic_error(std::string("Operation not supported") + std::to_string(monoms[1].first));
            }
        }
    }
};

std::shared_ptr<TSuper> operator+(const std::shared_ptr<TFunction>& a, const std::shared_ptr<TFunction>& b) {

    auto ret = std::make_shared<TSuper>();
    ret->monoms.emplace_back(std::make_pair('+', a));
    ret->monoms.emplace_back(std::make_pair('+', b));
    return ret;
}

std::shared_ptr<TSuper> operator-(const std::shared_ptr<TFunction>& a, const std::shared_ptr<TFunction>& b) {
    auto ret = std::make_shared<TSuper>();
    ret->monoms.emplace_back(std::make_pair('+', a));
    ret->monoms.emplace_back(std::make_pair('-', b));
    return ret;
}

std::shared_ptr<TSuper> operator*(const std::shared_ptr<TFunction>& a, const std::shared_ptr<TFunction>& b) {
    auto ret = std::make_shared<TSuper>();
    ret->monoms.emplace_back(std::make_pair('+', a));
    ret->monoms.emplace_back(std::make_pair('*', b));
    return ret;
}

std::shared_ptr<TSuper> operator/(const std::shared_ptr<TFunction>& a, const std::shared_ptr<TFunction>& b) {
    auto ret = std::make_shared<TSuper>();
    ret->monoms.emplace_back(std::make_pair('+', a));
    ret->monoms.emplace_back(std::make_pair('/', b));
    return ret;
}


template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator+(const std::shared_ptr<TFunction>& a, const T& b) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator+(const T& b, const std::shared_ptr<TFunction>& a) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator-(const std::shared_ptr<TFunction>& a, const T& b) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator-(const T& b, const std::shared_ptr<TFunction>& a) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator*(const std::shared_ptr<TFunction>& a, const T& b) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator*(const T& b, const std::shared_ptr<TFunction>& a) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator/(const std::shared_ptr<TFunction>& a, const T& b) {
    throw std::logic_error("Invalid operand type");
}
template <class T>
typename std::enable_if<!std::is_convertible<std::shared_ptr<TFunction>, T>::value, std::shared_ptr<TSuper>>::type operator/(const T& b, const std::shared_ptr<TFunction>& a) {
    throw std::logic_error("Invalid operand type");
}





class FuncFactory {
public:
    FuncFactory() = default;
    ~FuncFactory() = default;

    std::shared_ptr<TFunction> Create(const std::string type, const std::initializer_list<double> &val) {
        if (type == "ident") {
            return std::make_shared<TIdent>(val);
        } else if (type == "const") {
            return std::make_shared<TConst>(val);
        } else if (type == "power") {
            return std::make_shared<TPower>(val);
        } else if (type == "exp") {
            return std::make_shared<TExp>(val);
        } else if (type == "polynom") {
            return std::make_shared<TSuper>(val);
        } else {
            throw std::logic_error("Type not found");
        }
    }

};

double GradientRoot(TFunction& f, double x0 = 0, int it = 1000) {
    double fx0 = f.getValue(x0);
    for (int i = 1; i <= it && std::abs(fx0) > 1e-5; ++i) {
        double alpha = 0.01;
        x0 = x0 + alpha * ((fx0 > 0) ? -f.getDerivative(x0) : f.getDerivative(x0));
        fx0 = f.getValue(x0);
    }
    return x0;
}




#endif