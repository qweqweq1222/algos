#include<iostream>
#include<algorithm>
#include<exception>
class Rational
{
public:
    Rational() = default;
    Rational(const Rational& rat) = default;
    ~Rational() = default;
    Rational(const int num,const int den = 1);

    Rational& operator +=(const Rational& right) noexcept;
    Rational& operator -=(const Rational& right) noexcept;
    Rational& operator *=(const Rational& right) noexcept;
    Rational& operator /=(const Rational& right);
    Rational operator -() noexcept;

    int getNum() const;
    int getDen() const;

    bool operator == (const Rational& right) const noexcept;

private:
    int numerator = 0;
    int denominator = 1;

    const int gcd(const int& num,const int& den);
    void sign(Rational& r);
    void normalize(Rational& r);

};

bool operator != (const Rational& left, const Rational& right);
Rational operator + (const Rational& left, const Rational& right);
Rational operator - (const Rational& left, const Rational& right);
Rational operator * (const Rational& left, const Rational& right);
Rational operator / (const Rational& left, const Rational& right);
std::ostream& operator << (std::ostream& out, const Rational& right);

std::istream& operator >> (std::istream& in, Rational& right);