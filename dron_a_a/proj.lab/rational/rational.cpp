#include<iostream>
#include<algorithm>
#include<exception>
#include "rational.h"
#include <sstream>

    Rational::Rational(const int num,const int den): numerator(num), denominator(den)
    {
        if (den == 0) throw std::invalid_argument("Denominator must not be 0.");
        sign(*this);
        normalize(*this);
    }

    Rational& Rational::operator +=(const Rational& right) noexcept
    {
        this->numerator = this->numerator * right.denominator + right.numerator * this->denominator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& Rational::operator -=(const Rational& right) noexcept
    {
        this->numerator = this->numerator * right.denominator - right.numerator * this->denominator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& Rational::operator *=(const Rational& right) noexcept
    {
        this->numerator *= right.numerator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& Rational::operator /=(const Rational& right)
    {
        if(right.numerator == 0)
            throw std::invalid_argument("dividing by 0.");
        else
        {
            this->numerator *= right.denominator;
            this->denominator *= right.numerator;
            sign(*this);
            normalize(*this);
        }
        return *this;
    }
    Rational Rational::operator -() noexcept
    {
        return Rational(-numerator,denominator);
    }

    bool Rational::operator == (const Rational& right) const noexcept
    {
        return (this->numerator == right.numerator && this->denominator == right.denominator);
    }

    const int Rational::gcd(const int& num,const int& den)
    {
        int max = (num > den) ? num : den;
        int min = (num > den) ? den : num;
        while(min)
        {
            max %= min;
            std::swap(max,min);
        }
        return max;
    }
    void Rational::sign(Rational& r)
    {
        if(r.denominator < 0)
        {
            r.denominator -= 2*r.denominator;
            r.numerator -= 2*numerator;
        }
    }
    void Rational::normalize(Rational& r)
    {
        int gcd_ = gcd(r.numerator, r.denominator);
        while(gcd_ != 1)
        {
            r.numerator /= gcd_;
            r.denominator /= gcd_;
            gcd_ = gcd(r.numerator, r.denominator);
        }
    }
bool operator != (const Rational& left, const Rational& right)
{
    return !(left == right);
}
Rational operator + (const Rational& left, const Rational& right)
{
    return Rational(left) += right;
}
Rational operator - (const Rational& left, const Rational& right)
{
    return Rational(left) -= right;
}
Rational operator * (const Rational& left, const Rational& right)
{
    return Rational(left) *= right;
}
Rational operator / (const Rational& left, const Rational& right)
{
    return Rational(left) /= right;
}

int Rational::getNum() const
{
    return numerator;
}

int Rational::getDen() const
{
    return denominator;
}
std::ostream& operator << (std::ostream& out, const Rational& right)
{
    out << right.getNum() << "/" << right.getDen() << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Rational& right)
{
    std::string ss;
    int first_size = 0;
    int numerator = 0;
    int denominator = 0 ;
    std::cout << "numerator/denominator:";
    getline(in, ss);

    numerator = std::stoi(ss);
    first_size = std::to_string(numerator).length();
    ss.erase(ss.begin(), ss.begin() + first_size + 1);
    denominator = std::stoi(ss);

    if(denominator == 0)
        throw std::invalid_argument("Denominator must not be 0.");

    right = Rational(numerator, denominator);

    return in;
}