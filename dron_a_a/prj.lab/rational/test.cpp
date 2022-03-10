#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>
#include <sstream>
#include <iosfwd>

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

TEST_CASE("comparison operations")
{
    Rational small_number(2, 3);
    Rational second_small_number(2, 3);
    Rational big_number(5, 6);
    CHECK(small_number == second_small_number);
    CHECK(small_number <= second_small_number);
    CHECK(small_number <= big_number);
    CHECK(small_number < big_number);
    CHECK(small_number != big_number);
    CHECK_FALSE(small_number > big_number);
    CHECK_FALSE(small_number >= big_number);
}

TEST_CASE("arithmetic operations")
{
    int iterCount = 5;
    for (int i = 0; i < iterCount; ++i)
    {
        int a = rand() % 100;
        int b = rand() % 100 + 1;
        int c = rand() % 100 + 1;
        int d = rand() % 100 + 1;
        Rational number_1(a, b);
        Rational number_2(c, d);
        Rational sum(a * d + b * c, b * d);
        Rational mult(a * c, b * d);
        Rational diff(a * d - b * c, b * d);
        Rational div(a * d, b * c);
        Rational result = number_1 - number_2;
        CHECK(number_1 + number_2 == sum);
        CHECK(number_1 * number_2 == mult);
        CHECK(number_1 - number_2 == diff);
        CHECK(number_1 / number_2 == div);
    }
}

TEST_CASE("zero case")
{
    Rational default_number;
    CHECK(default_number.num() == 0);
    CHECK(default_number.denum() == 1);
    Rational zero_number(0, 3);
    CHECK(zero_number == default_number);
}

TEST_CASE("same irreducible appearance case")
{
    int a = rand() % 10000;
    int b = rand() % 10000 + 1;
    Rational number_1(a, b);
    Rational number_2(-a, -b);
    int c = rand() % 1000 + 2;
    Rational number_3(a * c, b * c);
    Rational number_4(-a * c, -b * c);
    CHECK(number_1 == number_2);
    CHECK(number_1 == number_3);
    CHECK(number_1 == number_4);
}
TEST_CASE("only numerator")
{
    REQUIRE( Rational(5) == Rational(5,1));
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
    Rational r = Rational();
    std::cin >> r; //enter 5 2
    CHECK(r == Rational(5,2));
}

TEST_CASE(">> operator with only num")
{
    Rational r = Rational();
    CHECK_THROWS_WITH_AS( std::cin >> r, "num/denum", std::invalid_argument);
}

TEST_CASE(" >> ")
{
    Rational r1(5,2);
    Rational r2;
    std::stringstream  ss;

    ss << 5 << "/" << 2 << std::endl;
    ss >> r2;

    CHECK(r1 == r2);
}

TEST_CASE("<< operator_str")
{
    Rational r(5,2);

    std::stringstream out;
    std::stringstream buf;

    out << r;
    buf << 5 << "/" << 2 << std::endl;

    CHECK(out.str() == buf.str());
}
