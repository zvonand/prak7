#include "Function.h"
#include <stdexcept>
#include <memory>

std::shared_ptr<TFunction> TFunction::Create(std::string type, double param) {
    if (type == "ident") {
        return std::dynamic_pointer_cast<TFunction>(std::make_shared<TIdent>(param));
    } else if (type == "const") {
        return std::dynamic_pointer_cast<TFunction>(std::make_shared<TConst>(param));
    } else if (type == "power") {
        return std::dynamic_pointer_cast<TFunction>(std::make_shared<TPower>(param));
    } else if (type == "exp") {
        return std::dynamic_pointer_cast<TFunction>(std::make_shared<TExp>(param));
    } else {
        throw std::invalid_argument("Wrong function type");
    }
}

std::shared_ptr<TFunction> TFunction::Create(std::string type, std::vector<double> coeffVec) {
    TFunction* f;

    if (type == "polynomial") {

    } else {
        throw std::invalid_argument("Wrong function type");
    }
    return nullptr;
}

double TFunction::getDerivative(double x) {
    return 0;
}
