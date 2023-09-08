//
// Created by Frank Yang on 2023/8/14.
//

#include <iostream>
#include "Fraction.h"
#define INF 100000000

inline int recognizingInt(const std::string &str, int startingPoint, int endingPoint)
{
    int number = 0;

    for (int i = startingPoint; i <= endingPoint; i++)
        number += (int) (str[i] - 0x30) * (int) pow(10, endingPoint - i);

    return number;
}

inline double recognizingDouble(const std::string &str, int startingPoint, int endingPoint)
{
    double number = 0;

    int cur = startingPoint;
    for (int i = startingPoint; i <= endingPoint; i++)
        if (str[i] == '.')
        {
            cur = i;
            break;
        }

    number += recognizingInt(str, startingPoint, cur - 1);

    int doublePart = recognizingInt(str, cur + 1, endingPoint);
    number += (double) doublePart / pow(10, endingPoint - cur);

    return number;
}

inline Fraction intToFraction(const int &i, bool isPositive)
{
    return isPositive ? Fraction(i,1) : Fraction(-i,1);
}

inline Fraction doubleToFraction(const double &d, bool isPositive)
{
    Fraction temp;

    int times = 1;
    for (int i = 1; i <= 1000000; i *= 10)
        if (!((float) (d * i) - (int) (d * i)))
        {
            times = i;
            i = INF;
        }

    temp = Fraction(isPositive ? (int) (d * times) : (int) (- d * times), (unsigned int) times);

    temp.update();

    return temp;
}

inline Fraction fractionConvert(const std::string &str, int startingPoint, int endingPoint)
{
    bool isDouble = false;
    bool isPositive = (str[startingPoint] != '-');

    for (int i = isPositive ? startingPoint : startingPoint + 1; i <= endingPoint; i++) {
        if (str[i] == '.')
        {
            isDouble = true;
            break;
        }
    }

    if (isDouble)
        return doubleToFraction(recognizingDouble(str, isPositive ? startingPoint : startingPoint + 1, endingPoint), isPositive);
    else
        return intToFraction(recognizingInt(str, isPositive ? startingPoint : startingPoint + 1, endingPoint), isPositive);
}
