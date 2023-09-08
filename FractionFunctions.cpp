#include <iostream>
#include "Fraction.h"
#define INF 100000000

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b > 0)
    {
        unsigned int r = a%b;
        a = b;
        b = r;
    }
    return a;
}

Fraction::Fraction(int num, unsigned int deno)
{
    numerator = num;
    denominator = deno;
}

void Fraction::update()
{
    bool isPositive = (numerator >= 0);
    if (!isPositive) numerator = -numerator;

    // Judge whether numerator/denominator is the most simplified
    unsigned int g = gcd(abs(numerator),denominator);

    if (g == 1)
    {
        if (!isPositive) numerator = -numerator;
        return;
    }
    else
    {
        while (g > 1)
        {
            numerator /= g;
            denominator /= g;
            g = gcd(abs(numerator),denominator);
        }
        if (!isPositive) numerator = -numerator;
        return;
    }
}

void Fraction::modify(int num, unsigned int deno)
{
    int temp = numerator;
    numerator = num;
    if (!deno)
    {
        std::cerr << "ERROR DENOMINATOR" << std::endl;
        numerator = temp;
        return;
    }
    else
    {
        denominator = deno;
        update();
        return;
    }
}

std::string Fraction::fractionToString() const
{
    std::string temp = "";

    if (!this->numerator)
    {
        temp = '0';
        return temp;
    }

    bool isPositive = (this->numerator >= 0);
    if (!isPositive) temp += '-';

    int num = abs(this->numerator);
    int deno = this->denominator;

    unsigned int sizeOfNumerator = (int) log10(num);
    unsigned int sizeOfDenominator = (int) log10(deno);

    for (int i = sizeOfNumerator; i >= 0; i--)
    {
        temp += (char) (num / pow(10, i) + 0x30);
        num -= (int) (num / pow(10, i)) * pow(10, i);
    }

    temp += '/';

    for (int i = sizeOfDenominator; i >= 0; i--) {
        temp += (char) (deno / pow(10, i) + 0x30);
        deno -= (int) (deno / pow(10, i)) * pow(10, i);
    }

    return temp;
}

Fraction Fraction::getOpposite() const
{
    Fraction temp;
    temp.numerator = -(this->numerator);
    temp.denominator = this->denominator;
    return temp;
}

Fraction Fraction::operator+ (const Fraction &f) const
{
    Fraction temp;
    temp.denominator = this->denominator * f.denominator;
    temp.numerator = this->numerator * f.denominator + f.numerator * this->denominator;
    temp.update();
    return temp;
}

Fraction Fraction::operator- (const Fraction &f) const
{
    Fraction temp, f_negative;
    f_negative = f;
    f_negative.numerator = -f.numerator;
    temp = *this + f_negative;
    temp.update();
    return temp;
}

Fraction Fraction::operator*(const Fraction &f) const
{
    Fraction temp;
    temp.numerator = this->numerator * f.numerator;
    temp.denominator = this->denominator * f.denominator;
    temp.update();
    return temp;
}

Fraction Fraction::getReciprocal() const
{
    Fraction temp;
    temp.numerator = (this->numerator >= 0) ? this->denominator : -(this->denominator);
    temp.denominator = abs(this->numerator);
    return temp;
}

Fraction Fraction::operator/(const Fraction &f) const
{
    Fraction temp;
    temp = *this * f.getReciprocal();
    temp.update();
    return temp;
}

Fraction::~Fraction()
{
    // std::cout << "FRACTION DATA CLEARED" <<std::endl;
}

