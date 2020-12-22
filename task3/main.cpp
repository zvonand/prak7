#include <iostream>
#include "CustomMath.h"

int main() {
    auto ff = FuncFactory();

    auto ex = ff.Create("exp", {1, 1});

    std::cout << GradientRoot(ex, 0, 10000) << std::endl;

    return 0;
}
