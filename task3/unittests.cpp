#include "gtest/gtest.h"
#include "CustomMath.h"


class CustomMath : public::testing::Test {
protected:
    const double prec = 10e-2;
    std::shared_ptr<TFunction> exponential_1, exponential_2, ident, power_func_1,
            power_func_2, power_func_3, power_func_4, constant, polynom, sum, diff, prod, quot, db1, db2;

    void SetUp(){
        auto ff = FuncFactory();
        exponential_1 = ff.Create("exp", {1.5, 2.7});
        exponential_2 = ff.Create("exp", {1.5, 0});
        ident = ff.Create("ident", {});
        power_func_1 = ff.Create("power", {0, 4});
        power_func_2 = ff.Create("power", {1, 1});
        power_func_3 = ff.Create("power", {4, 0});
        power_func_4 = ff.Create("power", {-4, 5});
        constant = ff.Create("const", {-12.34});
        polynom = ff.Create("polynom", {0, 1, 2, 3});

        sum = exponential_1 + power_func_2;
        diff = polynom - constant;
        prod = power_func_4 * ident;
        quot = power_func_4 / power_func_2;
        db1 = diff + quot;
        db2 = sum - prod;
    }

    void TearDown(){};
};



TEST_F(CustomMath, To_String_Test) {
    // CustomMath.h should support proper output for basic function types
    ASSERT_STREQ(ident->toString().c_str(), "x");
    ASSERT_STREQ(constant->toString().c_str(), "-12.34");
    ASSERT_STREQ(exponential_1->toString().c_str(), "1.5*e^2.7x");
    ASSERT_STREQ(exponential_2->toString().c_str(), "1.5");
    ASSERT_STREQ(power_func_1->toString().c_str(), "0");
    ASSERT_STREQ(power_func_2->toString().c_str(), "x");
    ASSERT_STREQ(power_func_3->toString().c_str(), "4");
    ASSERT_STREQ(power_func_4->toString().c_str(), "-4*x^5");
    ASSERT_STREQ(polynom->toString().c_str(), "(x) + (2*x^2) + (3*x^3)");
};

TEST_F(CustomMath, Get_Value_Test) {
    // CustomMath.h should provide correct result when calling getValue()
    ASSERT_NEAR(ident->getValue(123), 123, prec);
    ASSERT_NEAR(constant->getValue(555.7), -12.34, prec);
    ASSERT_NEAR(exponential_1->getValue(2), 332.11, prec);
    ASSERT_NEAR(exponential_2->getValue(2.234), 1.5, prec);
    ASSERT_NEAR(power_func_1->getValue(11), 0, prec);
    ASSERT_NEAR(power_func_2->getValue(12.34), 12.34, prec);
    ASSERT_NEAR(power_func_3->getValue(11), 4, prec);
    ASSERT_NEAR(power_func_4->getValue(2), -128, prec);
    ASSERT_NEAR(polynom->getValue(2), 34, prec);
};

TEST_F(CustomMath, Get_Derivative_Test) {
    // CustomMath.h should provide correct result when calling getDerivative()
    ASSERT_NEAR(ident->getDerivative(123), 1, prec);
    ASSERT_NEAR(constant->getDerivative(555.7), 0, prec);
    ASSERT_NEAR(exponential_1->getDerivative(2), 896.696, prec);
    ASSERT_NEAR(exponential_2->getDerivative(2.234), 0, prec);
    ASSERT_NEAR(power_func_1->getDerivative(11), 0, prec);
    ASSERT_NEAR(power_func_2->getDerivative(12.34), 1, prec);
    ASSERT_NEAR(power_func_3->getDerivative(11), 0, prec);
    ASSERT_NEAR(power_func_4->getDerivative(2), -320, prec);
    ASSERT_NEAR(polynom->getDerivative(2), 45, prec);
};


TEST_F(CustomMath, Get_Complex_Value_Test) {
    // Values of complex functions should be computed correctly
    ASSERT_NEAR(sum->getValue(3), 4944.7, prec);
    ASSERT_NEAR(diff->getValue(3), 114.34, prec);
    ASSERT_NEAR(prod->getValue(3), -2916, prec);
    ASSERT_NEAR(quot->getValue(3), -324, prec);
    ASSERT_NEAR(db1->getValue(3), -209.66, prec);
}

TEST_F(CustomMath, Get_Complex_Deerivative_Test) {
    // Derivatives of complex functions should be computed correctly
    ASSERT_NEAR(sum->getDerivative(3), 13343.6, prec);
    ASSERT_NEAR(diff->getDerivative(3), 94, prec);
    ASSERT_NEAR(prod->getDerivative(3), -5832, prec);
    ASSERT_NEAR(quot->getDerivative(3), -432, prec);
    ASSERT_NEAR(db1->getDerivative(3), -338, prec);
}

TEST_F(CustomMath, Gradient_Descent_Test) {
    // Gradient descent should converge to pre-known value
    ASSERT_NEAR(GradientRoot(diff, -2, 100000), -1.779, 0.01);
    ASSERT_NEAR(GradientRoot(db2, -0.5, 100000), -0.4355, 0.1);
    ASSERT_NEAR(GradientRoot(polynom, 0.5, 100000), 0, 0.01);
}