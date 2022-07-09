#include "ComplexNumber.hpp"

static const ComplexNumber zero = ComplexNumber(0, 0);

ComplexNumber::ComplexNumber(double real, double imaginary) : _imaginary(imaginary), _real(real), Re(_real), Im(_imaginary)
{
}

ComplexNumber::ComplexNumber(const ComplexNumber& source) : _imaginary(source.Im), _real(source.Re), Re(_real), Im(_imaginary)
{
}

ComplexNumber::~ComplexNumber()
{
}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& number)
{
    // Поскольку operator<< является другом класса ComplexNumber, то мы имеем прямой доступ к членам ComplexNumber
    out << number._real << " + " << number._imaginary << "i";
    return out;
}

std::istream& operator>>(std::istream& in, ComplexNumber& number)
{
    in >> number._real >> number._imaginary;
    return in;
}

ComplexNumber ComplexNumber::operator=(const ComplexNumber& b)
{
    return ComplexNumber(b.Re, b.Im);
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& b) const
{
    return ComplexNumber(this->Re + b.Re, this->Im + b.Im);
}
ComplexNumber ComplexNumber::operator-(const ComplexNumber& b) const
{
    return ComplexNumber(this->Re - b.Re, this->Im - b.Im);
}
ComplexNumber ComplexNumber::operator*(const ComplexNumber& b) const
{
    return ComplexNumber(this->Re * b.Re, this->Im * b.Im);
}
ComplexNumber ComplexNumber::operator/(const ComplexNumber& b) const
{
    return ComplexNumber(this->Re / b.Re, this->Im / b.Im);
}

bool ComplexNumber::operator==(const ComplexNumber& b) const
{
    return this->Re == b.Re && this->Im == b.Im;
}
bool ComplexNumber::operator!=(const ComplexNumber& b) const
{
    return !(*this == b);
}

bool ComplexNumber::isCollinear(const ComplexNumber& a, const ComplexNumber& b)
{
    return true;
}

bool ComplexNumber::isOnSameLine(const ComplexNumber& a, const ComplexNumber& b, const ComplexNumber& c)
{
    return true;
}

ComplexNumber ComplexNumber::middle(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber((a.Re + b.Re) / 2, (a.Im + b.Im) / 2);
}