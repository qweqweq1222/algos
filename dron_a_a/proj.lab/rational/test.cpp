#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"
TEST_SUITE("operators:")
{
    Rational r_1 (50,100); // 1/2
    Rational r_2 (5,-15); // -1/3
    Rational buffer = Rational();
    TEST_CASE("+, +=")
    {
        buffer = r_1 + r_2;
        CHECK(buffer == Rational(1,6));
        buffer -= r_2;
        CHECK (buffer == r_1);
    }
    TEST_CASE("-")
    {
        buffer = r_1 - r_2;
        CHECK(buffer == Rational(5,6));
        buffer += r_2;
        CHECK (buffer == r_1);
    }
    TEST_CASE("*")
    {
        buffer = r_1 * r_2;
        CHECK(buffer == Rational(-1,6));
        buffer /= r_2;
        CHECK (buffer == r_1);
    }
    TEST_CASE("/")
    {
        buffer = r_1 / r_2;
        CHECK(buffer == Rational(-3,2));
        buffer *= r_2;
        CHECK (buffer == r_1);
    }
}
TEST_CASE("zero denominator")
{
    CHECK_THROWS_WITH_AS(Rational(5,0),"Denominator must not be 0.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Rational(5,0),"Denominator must not be 0.", std::invalid_argument);
    SUBCASE("divide by zero")
    {
        Rational numerator(5,4);
        Rational denominator(0,1);
        CHECK_THROWS_WITH_AS(numerator /= denominator, "dividing by 0.", std::invalid_argument);
    }
}
TEST_CASE(">> operator")
{
    Rational r = Rational(5);
    std::cin >> r; //enter 5 2
    CHECK(r == Rational(5,2));
}
