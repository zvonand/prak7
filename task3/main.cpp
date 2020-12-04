#include <iostream>
#include "CustomMath.h"

int main() {
    auto ff = FuncFactory();

    auto power = ff.Create("power", {2, 3});
    std::cout << power->toString() << " val(1): " << power->getValue(1) << " der(2): " << power->getDerivative(2) << std::endl;

    auto poly = ff.Create("polynom", {1, 2, 3, 4});
    std::cout << poly->toString() << " val(1): " << poly->getValue(1) << " der(2): " << poly->getDerivative(2) << std::endl;

    auto sum = power + poly;
    std::cout << sum->toString() << " val(1): " << sum->getValue(1) << " der(2): " << sum->getDerivative(2) << std::endl;

    auto sub = power - poly;
    std::cout << sub->toString() << " val(1): " << sub->getValue(1) << " der(2): " << sub->getDerivative(2) << std::endl;

    auto mul = power * poly;
    std::cout << mul->toString() << " val(1): " << mul->getValue(1) << " der(2): " << mul->getDerivative(2) << std::endl;

    auto div = power / poly;
    std::cout << div->toString() << " val(1): " << div->getValue(1) << " der(2): " << div->getDerivative(2) << std::endl;

    auto exp = ff.Create("exp", {2, 3});
    auto ddd = power + exp;
    std::cout << ddd->toString() << " val(1): " << ddd->getValue(1) << " der(2): " << ddd->getDerivative(2) << std::endl;

    return 0;
}
