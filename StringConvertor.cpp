// std::string to QString


#include <iostream>
#include <QString>
#include <cmath>

#define MAXPOWERALLOWED 5

inline std::string removeLineChange(const std::string &str)
{
    if (!str.size())
        return str;

    std::string temp = "";

    for (int i = 0; i <= str.size()-1; i++)
        if (str[i] != '\n')
            temp += str[i];

    return temp;
}

inline QString QRemoveLineChange(QString _str)
{
    if (!_str.size())
        return _str;

    QString temp = "";

    for (int i = 0; i <= _str.size()-1; i++)
        if (_str[i] != '\n')
            temp += _str[i];

    return temp;
}

inline QString stringConvert(std::string str)
{
    str = removeLineChange(str);

    if (!str.size())
        return "USER_NOT_INPUT";

    QString _str = "";

    for (long long int i=0; i<=str.size()-1; i++)
        _str += str[i];

    return _str;
}

inline std::string QStringConvert(QString _str)
{
    _str = QRemoveLineChange(_str);

    if (!_str.size())
        return "USER_NOT_INPUT";

    return _str.toStdString();
}

inline QString unsignedIntConvert(unsigned long long int i)
{
    QString _str = "";

    if (i == 0) {
        _str = "0";
        return _str;
    }

    int digits = 0;

    for (long int j = i; j; j /= 10) {
        digits++;
    }

    for (long int j = digits; j >= 1; j--) {
        _str += (char)((unsigned int)(i % (long int)pow(10,j)) / (long int)pow(10, j - 1) + 0x30);
    }

    return _str;
}

inline double stringFractionToDouble(std::string &str)
{
    double d = 0;
    unsigned long int divisionPosition = -1;

    for (int i = 0; i <= str.size() - 1; i++)
        if (str[i] == '/')
        {
            divisionPosition = i;
            break;
        }

    long long int strNumerator = 0;
    long long int strDenominator = 0;

    for (long int i = divisionPosition - 1; i >= (str[0] == '-') ? 1 : 0; i--)
        strNumerator += (int)(str[i] - 0x30) * (long long int)pow(10,
                (divisionPosition - ((str[0] == '-') ? 1 : 0)) - // digits of numerator
                (i - ((str[0] == '-') ? 1 : 0) + 1) );

    for (int i = str.size() - 1; i >= divisionPosition + 1; i--)
        strDenominator += (int)(str[i] - 0x30) * (long long int)pow(10,
                (str.size() - 1 - divisionPosition) - // digits of denominator
                (i - divisionPosition) );

    d = (str[0] == '-') ? (- (double)strNumerator / (double)strDenominator) : ((double)strNumerator / (double)strDenominator);

    return d;
}

inline QString doubleConvert(double d) // The double parameter here must be a 'real' decimal
{
    QString _str = "";

    if (d < 0) _str += '-';

    unsigned long long int intPart = (d < 0) ? (long long int)(- d) : (long long int)d;
    _str += unsignedIntConvert(intPart);

    double doublePart = ((d < 0) ? (- d) : d) - (double)intPart; // a decimal that is in [0,1).

    unsigned int powRequired = 0;
    unsigned int moreZeroRequired = 0;

    for (powRequired = 1; powRequired <= MAXPOWERALLOWED; powRequired++)
    {
        if (doublePart * pow(10, powRequired) < 1) {
            moreZeroRequired++;
        }

        if ((doublePart * pow(10, powRequired) - (double)((long long int)(doublePart * pow(10, powRequired)))) < 1e-10) {
            // 1e-10 to prevent the 'remainder' from type conversion.
            break;
        }
    }

    _str += '.';

    if (moreZeroRequired) {
        for (int i = 1; i <= moreZeroRequired; i++) {
            _str += '0';
        }
    }

    unsigned int intFormOfDoublePart = (unsigned long long int)(doublePart * pow(10, powRequired));
    _str += unsignedIntConvert(intFormOfDoublePart);


    return _str;
}
