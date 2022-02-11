//
// Created by anreydron on 10.02.2022.
//
#include<iostream>
template<class T>
class Rational {
private:
    T data;
public:
    Rational(T data): data(data) {}
    Rational(const Rational rat)
    {

    }
    ~Rational();
    Rational operator=(Rational a)
    {
        return Rational();
    }
    Rational operator+(Rational b)
    {
        return Rational();
    }

};
int main(void)
{
    return 0;
}
