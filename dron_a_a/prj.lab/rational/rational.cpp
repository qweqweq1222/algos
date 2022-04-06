#include<iostream>
#include<algorithm>
#include<exception>
#include <rational/rational.h>
#include <sstream>
#include <string>
#include <utility>


Rational::Rational(const int num,const int den): numerator(num), denominator(den) {
    if (den == 0) throw std::invalid_argument("Denominator must not be 0.");
    normalize(*this);
}

Rational::Rational(Rational&& rhs) noexcept: numerator(rhs.numerator), denominator(rhs.denominator) {
    rhs.numerator = 0;
    rhs.denominator = 1;
}

Rational& Rational::operator = (Rational&& rhs) noexcept {
    numerator = rhs.numerator;
    denominator = rhs.denominator;

    rhs.numerator = 0;
    rhs.denominator = 1;

    return *this;
}
Rational::Rational(const int num): numerator(num), denominator(1) {}

Rational& Rational::operator +=(const Rational& rhs) noexcept {
    this->numerator = this->numerator * rhs.denominator + rhs.numerator * this->denominator;
    this->denominator *= rhs.denominator;
    normalize(*this);
    return *this;
}

Rational& Rational::operator -=(const Rational& rhs) noexcept {
    this->numerator = this->numerator * rhs.denominator - rhs.numerator * this->denominator;
    this->denominator *= rhs.denominator;
    normalize(*this);
    return *this;
}

Rational& Rational::operator *=(const Rational& rhs) noexcept {
    this->numerator *= rhs.numerator;
    this->denominator *= rhs.denominator;
    normalize(*this);
    return *this;
}

Rational& Rational::operator /=(const Rational& rhs) {
    if (rhs.numerator == 0)
        throw std::invalid_argument("dividing by 0.");
    else {
        this->numerator *= rhs.denominator;
        this->denominator *= rhs.numerator;
        normalize(*this);
    }
    return *this;
}

Rational Rational::operator -() noexcept {
    return Rational(-numerator, denominator);
}

bool Rational::operator == (const Rational& rhs) const noexcept {
    return (this->numerator == rhs.numerator && this->denominator == rhs.denominator);
}

bool Rational::operator < (const Rational& rhs) const noexcept {
    return (numerator * rhs.denominator) < (rhs.numerator * denominator);
}

bool Rational::operator > (const Rational& rhs) const noexcept {
    return (numerator * rhs.denominator) > (rhs.numerator * denominator);
}

bool Rational::operator <= (const Rational& rhs) const noexcept {
    return (*this < rhs || *this == rhs);
}

bool Rational::operator >= (const Rational& rhs) const noexcept {
    return (*this > rhs || *this == rhs);
}

bool Rational::operator != (const Rational& rhs) const noexcept {
    return !(*this == rhs);
}

const int Rational::gcd(const int& num, const int& den) {
    int max = (num > den) ? num : den;
    int min = (num > den) ? den : num;
    while(min) {
        max %= min;
        std::swap(max, min);
    }
    return max;
}

void Rational::sign(Rational& r) {
    if (r.denominator < 0) {
        r.denominator -= 2*r.denominator;
        r.numerator -= 2*numerator;
    }
}

void Rational::normalize(Rational& r) {
    int gcd_ = gcd(r.numerator, r.denominator);
    while (abs(gcd_) != 1) {
        r.numerator /= gcd_;
        r.denominator /= gcd_;
        gcd_ = gcd(r.numerator, r.denominator);
    }
    sign(*this);
}

int Rational::num() const {
    return numerator;
}

int Rational::denum() const {
    return denominator;
}

std::istream& Rational::read_from(std::istream& istrm) {
	char minus = '-';
	if(!std::isdigit(istrm.peek()) && !(istrm.peek() == minus))
		istrm.clear(std::ios_base::failbit);
	else {
		istrm >> numerator;
		if(istrm.good()) {
			char sym = istrm.get();
			if (sym != '/')
				istrm.clear(std::ios_base::failbit);
				//istrm.setstate(std::ios_base::failbit);
			else {
				if(!std::isdigit(istrm.peek()))
					istrm.clear(std::ios_base::failbit);
				else {
					istrm >> denominator;
					if((istrm.good() && denominator > 0) || (istrm.rdstate() == std::ios_base::eofbit && denominator>0))
						normalize((*this));
					else if(istrm.eof())
						istrm.clear(std::ios_base::failbit | std::ios_base::eofbit);
					else
						istrm.clear(std::ios_base::failbit);
				}
				//istrm.setstate(std::ios_base::failbit);
			}
		}
		else {
			numerator = 0;
			denominator = 1;
			istrm.clear( std::ios_base::failbit );
		}
	}
	return istrm;
}

std::ostream& Rational::write_to(std::ostream& ostrm) const {
    ostrm << numerator << "/" << denominator;
    return ostrm;
}

std::ostream& operator << (std::ostream& ostrm, const Rational& r) {
    return r.write_to(ostrm);
}

std::istream& operator >> (std::istream& istrm, Rational& r) {
    return r.read_from(istrm);
}

const Rational operator+(const Rational& lhs, const int n) { return lhs + Rational(n); }
const Rational operator-(const Rational& lhs, const int n) { return lhs - Rational(n); }
const Rational operator*(const Rational& lhs, const int n) { return lhs * Rational(n); }
const Rational operator/(const Rational& lhs, const int n) { return lhs / Rational(n); }

const Rational operator+(const int n, const Rational& rhs) { return Rational(n) + rhs; }
const Rational operator-(const int n, const Rational& rhs) { return Rational(n) - rhs; }
const Rational operator*(const int n, const Rational& rhs) { return Rational(n) * rhs; }
const Rational operator/(const int n, const Rational& rhs) { return Rational(n) / rhs; }
