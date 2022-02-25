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

    Rational::Rational(Rational&& rhs) noexcept: numerator(rhs.numerator), denominator(rhs.denominator)
    {
        rhs.numerator = 0;
        rhs.denominator = 1;
    }

    Rational& Rational::operator = (Rational&& rhs) noexcept
    {
        numerator = rhs.numerator;
        denominator = rhs.denominator;

        rhs.numerator = 0;
        rhs.denominator = 1;

        return *this;
    }
    Rational::Rational(const int num): numerator(num), denominator(1){}

    Rational& Rational::operator +=(const Rational& rhs) noexcept
    {
        this->numerator = this->numerator * rhs.denominator + rhs.numerator * this->denominator;
        this->denominator *= rhs.denominator;
        normalize(*this);
        return *this;
    }

    Rational& Rational::operator -=(const Rational& rhs) noexcept
    {
        this->numerator = this->numerator * rhs.denominator - rhs.numerator * this->denominator;
        this->denominator *= rhs.denominator;
        normalize(*this);
        return *this;
    }

    Rational& Rational::operator *=(const Rational& rhs) noexcept
    {
        this->numerator *= rhs.numerator;
        this->denominator *= rhs.denominator;
        normalize(*this);
        return *this;
    }

    Rational& Rational::operator /=(const Rational& rhs)
    {
        if(rhs.numerator == 0)
            throw std::invalid_argument("dividing by 0.");
        else
        {
            this->numerator *= rhs.denominator;
            this->denominator *= rhs.numerator;
            sign(*this);
            normalize(*this);
        }
        return *this;
    }

    Rational Rational::operator -() noexcept
    {
        return Rational(-numerator,denominator);
    }

    bool Rational::operator == (const Rational& rhs) const noexcept
    {
        return (this->numerator == rhs.numerator && this->denominator == rhs.denominator);
    }

    bool Rational::operator < (const Rational& rhs) const noexcept
    {
        Rational diff = *this - rhs;
        return (diff.num() < 0);
    }

    bool Rational::operator > (const Rational& rhs) const noexcept
    {
        return !(*this < rhs);
    }

    bool Rational::operator <= (const Rational& rhs) const noexcept
    {
        return (*this < rhs || *this == rhs);
    }

    bool Rational::operator >= (const Rational& rhs) const noexcept
    {
        return !(*this <= rhs);
    }

    bool Rational::operator != (const Rational& rhs) const noexcept
    {
        return !(*this == rhs);
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

int Rational::num() const
{
    return numerator;
}

int Rational::denum() const
{
    return denominator;
}

std::ostream& operator << (std::ostream& ostrm, const Rational& r)
{
    ostrm << r.num() << "/" << r.denum() << std::endl;
    return ostrm;
}

std::istream& operator >> (std::istream& istrm, Rational& r)
{
    std::string ss;
    int first_size = 0;
    int numerator = 0;
    int denominator = 0 ;
    std::cout << "numerator/denominator:";
    getline(istrm, ss);

    numerator = std::stoi(ss);
    first_size = std::to_string(numerator).length();
    ss.erase(ss.begin(), ss.begin() + first_size + 1);
    denominator = std::stoi(ss);

    if(denominator <= 0 )
        throw std::invalid_argument("Denominator must not be 0.");

    r = Rational(numerator, denominator);

    return istrm;
}