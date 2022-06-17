#include "complexn.hpp"

static const ComplexNumber zero = ComplexNumber(0,0);

ComplexNumber::ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary), Re(real), Im(imaginary)
{
}

ComplexNumber::~ComplexNumber()
{
}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& number)
{
    // Поскольку operator<< является другом класса ComplexNumber, то мы имеем прямой доступ к членам ComplexNumber
    out << number.real << " + " << number.imaginary << "i";
    return out;
}

std::istream& operator>>(std::istream& in, ComplexNumber& number)
{
    // Поскольку operator>> является другом класса ComplexNumber, то мы имеем прямой доступ к членам ComplexNumber.
    in >> number.real >> number.imaginary;
    return in;
}
