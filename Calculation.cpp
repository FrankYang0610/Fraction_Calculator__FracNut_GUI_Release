//
// Created by Frank Yang on 2023/8/14.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include "Fraction.h"
#include "FractionConvertor.cpp"

inline std::vector <char> stringToVector(const std::string &str)
{
    std::vector <char> temp;

    for (int i = 0; i <= str.size()-1; i++)
        if (str[i] != ' ')
            temp.push_back(str[i]);

    return temp;
}

inline Fraction calculate(const std::string& str) // for calculating the expressions without any pair of parentheses
{
    Fraction result(0,1);

    bool startingFromPositive = (str[0] != '-');

    // THE EXPRESSIONS HERE ARE WITHOUT PARENTHESES

    // BLOCKING THE EXPRESSION
    std::queue <int> blockStart;
    std::queue <int> blockEnd;

    // STARTING BLOCKING
    bool scanningInFraction = false;
    blockStart.push(startingFromPositive ? 0 : 1);
    for (int i = startingFromPositive ? 0 : 1; i <= str.size() - 1; i++)
    {
        if (str[i] == '[')
            scanningInFraction = true;
        if (str[i] == ']')
            scanningInFraction = false;

        if ((str[i] == '+' || str[i] == '-') && !scanningInFraction) {
            blockEnd.push(i - 1);
            blockStart.push(i + 1);
        }
    }
    blockEnd.push(str.size() - 1);

    // THE NUMBER OF BLOCKS
    int blocks = blockStart.size();

    // START CALCULATING THE TIMES AND DIVISION
    bool isCurrentlyPlus = startingFromPositive;
    for (int i = 1; i <= blocks; i++) // calculate every block
    {
        Fraction currentResult = Fraction(1, 1);

        bool isCurrentlyTimes = true; // or, it is divides.
        bool isInFraction = false;
        int separatorLocation = 0;
        int lastOperatorLocation = blockStart.front() - 1;


        for (int j = blockStart.front(); j <= blockEnd.front(); j++) // in Block Scanning
        {

            if (str[j] == '[')
                isInFraction = true;

            if ((str[j] == '*' || str[j] == '/' || j == blockEnd.front()) && !isInFraction) // Processing the previous one
            {

                if (str[j - 1] != ']')
                    currentResult = isCurrentlyTimes ? (currentResult * fractionConvert(str, lastOperatorLocation + 1, (j == blockEnd.front()) ? j : j - 1)) :
                                        (currentResult / fractionConvert(str, lastOperatorLocation + 1, (j == blockEnd.front()) ? j : j - 1));
                lastOperatorLocation = j;
            }


            if (str[j] == '/')
            {
                if (!isInFraction) isCurrentlyTimes = false;
                else separatorLocation = j;
            }
            if (str[j] == '*')
                isCurrentlyTimes = true;


            if (str[j] == ']')
            {
                int startOfFraction = 0;
                for (int k = j; k >= blockStart.front(); k--)
                    if (str[k] == '[')
                    {
                        startOfFraction = k;
                        k = blockStart.front() - 1;
                    }

                Fraction recognizedFraction = fractionConvert(str, startOfFraction + 1, separatorLocation - 1) /
                                              fractionConvert(str, separatorLocation + 1, j - 1);

                if (isCurrentlyTimes) currentResult = currentResult * recognizedFraction;
                else currentResult = currentResult / recognizedFraction;

                isInFraction = false;
                separatorLocation = 0;
            }
        } // scan the current block

        // SAVE RESULT
        if (isCurrentlyPlus) result = result + currentResult;
        else result = result - currentResult;

        // ENDING
        if (blockEnd.size() > 1) // when blockEnd.front() + 1 is valid
        {
            if (str[blockEnd.front() + 1] == '-')
                isCurrentlyPlus = false;
            else
                isCurrentlyPlus = true;
        }

        blockStart.pop();
        blockEnd.pop();
    } // blocks

    result.update();

    return result;
}

inline Fraction recognizingExpression(const std::string &str)
{
    // REMOVE SPACEBARS
    std::vector <char> expression = stringToVector(str);


    // CHECK WHETHER THE PARENTHESES ARE PAIRED, ALONGSIDE WITH CALCULATING THE PAIRS
    std::stack <char> pairing;
    int pairs = 0; // IMPORTANT
    for (int i = 0; i <= expression.size() - 1; i++)
    {
        if (expression[i] == '(')
        {
            pairing.push('(');
            pairs++;
        }
        else if (expression[i] == ')') pairing.pop();
    }
    if (!pairing.empty())
    {
        std::cerr << "ERROR EXPRESSION: PARENTHESES PAIRING ERROR!" << std::endl;
        return Fraction(0, 1);
    }


    while (pairs)
    {
        // FIND THE INNER PARENTHESES
        int cur1 = 0, cur2 = expression.size() - 1;
        for (int i = 0; i <= expression.size() - 1; i++)
        {
            if (expression[i] == '(') cur1 = i;
            else if (expression[i] == ')') {
                cur2 = i;
                i = expression.size();
            }
        }

        // HERE WE CALCULATE THE FOLLOWING
        std::string toCalculate = "";
        for (int i = cur1 + 1; i <= cur2 - 1; i++)
            toCalculate += expression[i];
        Fraction temp = calculate(toCalculate);

        expression[cur1] = '[';
        expression[cur2] = ']';
        expression.erase(expression.begin() + cur1 + 1, expression.begin() + cur2);


        std::string tempString = temp.fractionToString();
        for (int i = 0; i <= tempString.size() - 1; i++)
            expression.insert(expression.begin() + cur1 + i + 1, tempString[i]);

        pairs--; // FINISH CALCULATING
    } // while

    std::string finalCalculate = "";
    for (int i = 0; i <= expression.size() - 1; i++)
        finalCalculate += expression[i];

    return calculate(finalCalculate);
}
