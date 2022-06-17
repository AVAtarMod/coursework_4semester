#ifndef COMPLEXN_LIB
#define COMPLEXN_LIB

#include <iostream>

class ComplexNumber {
private:
    double imaginary;
    double real;
    friend std::ostream& operator<<(std::ostream& out, const ComplexNumber& number);
    friend std::istream& operator>>(std::istream& in, ComplexNumber& number);

public:
    ComplexNumber(double real = 0, double imaginary = 0);
    ComplexNumber(const ComplexNumber& source);

    ComplexNumber operator=(const ComplexNumber& source);

    ComplexNumber  operator+(const ComplexNumber& b) const;
    ComplexNumber operator-(const ComplexNumber& b) const;
    ComplexNumber operator*(const ComplexNumber& b) const;
    ComplexNumber operator/(const ComplexNumber& b) const;

    bool operator==(const ComplexNumber& b) const;
    bool operator!=(const ComplexNumber& b) const;
    bool operator>(const ComplexNumber& b) const;
    bool operator<(const ComplexNumber& b) const;

    static bool isCollinear(const ComplexNumber& a, const ComplexNumber& b);
    static bool isOnSameLine(const ComplexNumber& a, const ComplexNumber& b, const ComplexNumber& c);

    static ComplexNumber middle(const ComplexNumber& a, const ComplexNumber& b);

    const double& Re;
    const double& Im;

    static ComplexNumber getZero()
    {
        return ComplexNumber(0, 0);
    }
    ~ComplexNumber();
};

#endif // COMPLEXN_LIB
