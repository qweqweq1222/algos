#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>
#include <sstream>
#include <iosfwd>

struct CheckData {
	std::string str;
	int nmr;
	int dmr;
};

const int gcd(const int& num, const int& den) {
    int max = (num > den) ? num : den;
    int min = (num > den) ? den : num;
    while (min) {
        max %= min;
        std::swap(max,min);
    }
    return max;
}
void normalize(int& numerator, int& denominator) {
    int gcd_ = gcd(numerator, denominator);
    while (abs(gcd_) != 1) {
        numerator /= gcd_;
        denominator /= gcd_;
        gcd_ = gcd(numerator, denominator);
    }
}

TEST_CASE("comparison operations") {
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

TEST_CASE("arithmetic operations") {
    int iterCount = 5;
    for (int i = 0; i < iterCount; ++i) {
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

TEST_CASE("zero case") {
    Rational default_number;
    CHECK(default_number.num() == 0);
    CHECK(default_number.denum() == 1);
    Rational zero_number(0, 3);
    CHECK(zero_number == default_number);
}

TEST_CASE("same irreducible appearance case") {
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
TEST_CASE("only numerator") {
    for (int i = 0; i < 50; ++i) {
        int nm = rand()%100;
        REQUIRE(Rational(nm) == Rational(nm, 1));
    }
}

TEST_CASE("zero denominator") {
    for (int i = 0; i < 50; ++i) {
        CHECK_THROWS_WITH_AS(Rational(rand()%100 + 1, 0), "Denominator must not be 0.", std::invalid_argument);
        SUBCASE("divide by zero") {
            Rational numerator(rand()%100 + 1, rand()%100 + 1);
            Rational denominator(0, rand()%100 + 1);
            CHECK_THROWS_WITH_AS(numerator /= denominator, "dividing by 0.", std::invalid_argument);
        }
    }
}

TEST_CASE(">> <<") {
    int counter = 100;
    int nm = 0;
    int dnm = 0;
	bool check_;
    std::string str;
    Rational fraction;
    SUBCASE(">>") {
        for (int i = 0; i < counter; ++i) {
            nm = rand()%counter;
            dnm = rand()%counter - counter/2;
            normalize(nm, dnm);
            str = std::to_string(nm) + "/" + std::to_string(dnm);
            std::stringstream str_strm(str);

            str_strm >> fraction;
            str_strm.rdstate();
			check_ = (str_strm.rdstate() == std::ios_base::failbit)|| (str_strm.rdstate() == (std::ios_base::failbit | std::ios_base::eofbit));
            if (dnm <= 0)
                CHECK(check_ == true);
            else
                CHECK(fraction == Rational(nm, dnm));
        }
    }
    SUBCASE("<<") {
        std::stringstream str1;
        std::stringstream str2;
        for (int i = 0; i < counter; ++i) {
            nm = rand()%counter;
            dnm = rand()%counter - counter/2;
            normalize(nm, dnm);

            if (dnm < 0) {
                str1 << -nm << "/" << -dnm;
                str2 << Rational(nm, dnm);
                CHECK(str1.str() == str2.str());
            }
            else if (dnm == 0)
                CHECK_THROWS_WITH_AS(Rational(nm, dnm), "Denominator must not be 0.", std::invalid_argument);
            else {
                str1 << nm << "/" << dnm;
                str2 << Rational(nm, dnm);
                CHECK(str1.str() == str2.str());
            }
        }
    }
}
TEST_CASE("<< >>")
{
	const std::vector<CheckData> check_data{{"3/4", 3, 4},
											{"-1/125", 1, -125},
											{"0/1", 0, 1},
											{"428/1517", -428, -1517},
											{"1/1", 1024, 1024},
											{"-8/9", -8, 9},
											{"17/380", 17, 380},
											{"-12345/1", 12345, -1}};

	SUBCASE(" << ") {
		for (auto frac : check_data) {
			std::stringstream output;
			Rational q1(frac.nmr, frac.dmr);

			output << q1;

			CHECK(output.str() == frac.str);
		}
	}

	SUBCASE("operator >>") {
			for (auto frac : check_data) {
				std::stringstream input(frac.str);
				Rational q1;

				input >> q1;

				CHECK(!input.fail());
				CHECK(Rational(frac.nmr, frac.dmr) == q1);
			}

			std::vector<const char*> bad_input{" 5/4", "16/0", "9/-81", "3 15", "4\\80", "1 / 25", "7/ 8", "5 /17"};

			for (auto str : bad_input) {
				std::stringstream input(str);
				Rational q1;

				input >> q1;
				CHECK(input.fail());
			}
		}
}

TEST_CASE("int arithmetic")
{
	bool checker = false;
	std::vector<int> int_numbers = {1, 2, 119, 52};
	std::vector<Rational> dr_number = {Rational(5,4), Rational(4,3), Rational(-3,2), Rational(1,2)};
	for(int i = 0; i < int_numbers.size(); ++i)
	{
		checker = (int_numbers[i] + dr_number[i]) == (Rational(int_numbers[i]) + dr_number[i]);
		CHECK(checker == true);
		checker = (int_numbers[i] - dr_number[i]) == (Rational(int_numbers[i]) - dr_number[i]);
		CHECK(checker == true);
		checker = (int_numbers[i] * dr_number[i]) == (Rational(int_numbers[i]) * dr_number[i]);
		CHECK(checker == true);
		checker = (int_numbers[i] / dr_number[i]) == (Rational(int_numbers[i]) / dr_number[i]);
		CHECK(checker == true);


		checker = (dr_number[i] + int_numbers[i]) == (dr_number[i] + Rational(int_numbers[i]));
		CHECK(checker == true);
		checker = (dr_number[i] - int_numbers[i]) == (dr_number[i] - Rational(int_numbers[i]));
		CHECK(checker == true);
		checker = (dr_number[i] * int_numbers[i]) == (dr_number[i] * Rational(int_numbers[i]));
		CHECK(checker == true);
		checker = (dr_number[i] / int_numbers[i]) == (dr_number[i] / Rational(int_numbers[i]));
		CHECK(checker == true);
	}
}
