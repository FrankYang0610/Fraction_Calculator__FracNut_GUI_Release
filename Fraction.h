//
// Created by Frank Yang on 2023/9/1.
//

#include <iostream>
#ifndef FRACTIONUTILITY_FRACTION_H
#define FRACTIONUTILITY_FRACTION_H


class Fraction
{
private:
    int numerator;
    unsigned int denominator;
public:
    explicit Fraction(int num=0, unsigned int deno=1);
    inline void show() const
    {
        if (denominator == 1) std::cout << numerator << std::endl;
        else if (numerator) std::cout << numerator << "/" << denominator << std::endl;
        else std::cout << 0 << std::endl;
    }
    void update();
    void modify(int num, unsigned int deno);

    std::string fractionToString() const;

    /* Operator overloading */
    // OPPOSITE
    Fraction getOpposite() const;

    // PLUS
    Fraction operator+ (const Fraction &f) const;

    //MINUS
    Fraction operator- (const Fraction &f) const;

    // MULTIPLICATION
    Fraction operator* (const Fraction &f) const;

    // RECIPROCAL
    Fraction getReciprocal() const;

    // DIVISION
    Fraction operator/ (const Fraction &f) const;

    ~Fraction();
};

#endif //FRACTIONUTILITY_FRACTION_H
