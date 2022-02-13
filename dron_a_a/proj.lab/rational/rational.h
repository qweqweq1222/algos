#include<iostream>
#include<algorithm>
#include<exception>
class Rational
{
public:
    Rational() = default;
    Rational(const Rational &rat) = default;
    ~Rational() = default;
    Rational(const int num,const int den = 1): numerator(num), denominator(den)
    {
        if (den == 0) throw std::invalid_argument("Denominator must not be 0.");
        sign(*this);
        normalize(*this);
    }

    Rational& operator +=(const Rational& right) noexcept
    {
        this->numerator = this->numerator * right.denominator + right.numerator * this->denominator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& operator -=(const Rational& right) noexcept
    {
        this->numerator = this->numerator * right.denominator - right.numerator * this->denominator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& operator *=(const Rational& right) noexcept
    {
        this->numerator *= right.numerator;
        this->denominator *= right.denominator;
        normalize(*this);
        return *this;
    }
    Rational& operator /=(const Rational& right)
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
    Rational operator -() noexcept
    {
        return Rational(-numerator,denominator);
    }

    bool operator == (const Rational &right) const noexcept
    {
        return (this->numerator == right.numerator && this->denominator == right.denominator);
    }

private:
    int numerator = 0;
    int denominator = 1;

    const int gcd(const int& num,const int& den)
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
    void sign(Rational& r)
    {
        if(r.denominator < 0)
        {
            r.denominator -= 2*r.denominator;
            r.numerator -= 2*numerator;
        }
    }
    void normalize(Rational& r)
    {
        int gcd_ = gcd(r.numerator, r.denominator);
        while(gcd_ != 1)
        {
            r.numerator /= gcd_;
            r.denominator /= gcd_;
            gcd_ = gcd(r.numerator, r.denominator);
        }
    }
    friend std::ostream& operator << (std::ostream &out, const Rational &right);
    friend std::istream & operator >> (std::istream &in, Rational &right);
};

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

std::ostream& operator << (std::ostream &out, const Rational& right)
{
    out << right.numerator << "/" << right.denominator << std::endl;
    return out;
}

std::istream& operator >> (std::istream &in, Rational &right)
{
    std::cout << "numerator:";
    in >> right.numerator;
    std::cout << "denominator:";
    in >> right.denominator;

    if(right.denominator == 0)
        throw std::invalid_argument("Denominator must not be 0.");

    right.sign(right);
    right.normalize(right);

    return in;
}