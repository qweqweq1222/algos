#include<iostream>
#include<algorithm>
#include<exception>
class Rational
{
public:
    Rational() = default;
    Rational(const Rational& rat) = default;
    Rational(const int num,const int den);
    explicit Rational(const int num);
    Rational(Rational&& rhs) noexcept;
    ~Rational() = default;

    Rational& operator=(Rational&&) noexcept;

    Rational& operator +=(const Rational& rhs) noexcept;
    Rational& operator -=(const Rational& rhs) noexcept;
    Rational& operator *=(const Rational& rhs) noexcept;
    Rational& operator /=(const Rational& rhs);
    Rational operator -() noexcept;

    int num() const;
    int denum() const;

    bool operator == (const Rational& rhs) const noexcept;
    bool operator != (const Rational& rhs) const noexcept;
    bool operator<(const Rational& rhs) const noexcept;
    bool operator>(const Rational& rhs) const noexcept;
    bool operator<=(const Rational& rhs) const noexcept;
    bool operator>=(const Rational& rhs) const noexcept;

private:
    int numerator = 0;
    int denominator = 1;

    const int gcd(const int& num,const int& den);
    void sign(Rational& r);
    void normalize(Rational& r);

};

inline Rational operator + (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) += rhs;
}
inline Rational operator - (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) -= rhs;
}
inline Rational operator * (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) *= rhs;
}
inline Rational operator / (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) /= rhs;
}

std::ostream& operator << (std::ostream& ostrm, const Rational& r);
std::istream& operator >> (std::istream& istrm, Rational& r);