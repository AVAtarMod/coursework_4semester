#include "Line.hpp"
#include "functions.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

class LineEquation {
private:
    Point _pointA, _pointB;
    double _k, _b, _x, _y;
    double xDiff, yDiff;
    bool _inited = false;
    LineType type;

    void initByLineType();

public:
    LineEquation() {};
    LineEquation(const Point& a, const Point& b);
    LineEquation(const ComplexNumber& a, const ComplexNumber& b);

    double K() const { return _k; }
    double B() const { return _b; }

    double xConst() const { return _x; }
    double yConst() const { return _y; }

    bool isInited() const { return _inited; }

    LineType getType() const { return type; }
};

void Line::finishInit(const LineEquation& initedEquation)
{
    if (!initedEquation.isInited())
        throw std::runtime_error("Cannot finish line initialization with not inited equation!");

    _k = initedEquation.K();
    _b = initedEquation.B();
    _type = initedEquation.getType();
    switch (_type) {
    case LineType::CONST_X:
        _x = initedEquation.xConst();
        break;
    case LineType::CONST_Y:
        _y = initedEquation.yConst();
        break;
    default:
        break;
    }
}

Line::Line(const std::pair<Point, Point>& pair)
{
    LineEquation equation = LineEquation(pair.first, pair.second);
    finishInit(equation);
}

Line::Line(const ComplexNumber& first, const ComplexNumber& second)
{
    LineEquation equation = LineEquation(first, second);
    finishInit(equation);
}

double Line::y(double x) const
{
    switch (_type) {
    case LineType::CONST_X:
        return (_x == x)
            ? std::numeric_limits<double>::infinity()
            : 0;
    case LineType::CONST_Y:
        return _y;
    case LineType::NORMAL:
        return _k * x + _b;
    default:
        return 0;
    }
}

double Line::x(double y) const
{
    switch (_type) {
    case LineType::CONST_X:
        return _x;
    case LineType::CONST_Y:
        return (_y == y)
            ? std::numeric_limits<double>::infinity()
            : 0;
    case LineType::NORMAL:
        return (y - _b) / _k;
    default:
        return 0;
    }
}

bool Line::isInX(double x) const
{
    switch (_type) {
    case LineType::CONST_X:
        return _x == x;
    case LineType::CONST_Y:
    case LineType::NORMAL:
        return true;
    default:
        return false;
    }
}

bool Line::isInY(double y) const
{
    switch (_type) {
    case LineType::CONST_X:
    case LineType::NORMAL:
        return true;
    case LineType::CONST_Y:
        return _y == y;
    default:
        return 0;
    }
}

bool Line::isBelongs(Point point)
{
    switch (_type) {
    case LineType::CONST_X:
        return _x == point.X();
    case LineType::CONST_Y:
        return _y == point.Y();
    case LineType::NORMAL:
        return almost_equal(y(point.X()), point.Y(), 2);
    default:
        return false;
    }
}

// LineEquation section

void LineEquation::initByLineType()
{
    switch (type) {
    case LineType::CONST_X:
        // Y may be any, x = const
        _k = 0;
        _b = std::numeric_limits<double>::infinity();
        _x = _pointB.X();
        break;
    case LineType::CONST_Y:
        // X may be any, y = const
        _k = 0;
        _b = 0;
        _y = _pointB.Y();
        break;
    case LineType::NORMAL:
        // Normal line, y = kx + b
        _k = yDiff / xDiff;
        _b = (-_pointA.X() * yDiff + _pointA.Y() * xDiff) / xDiff;
        break;
    default:
        break;
    }
}

LineEquation::LineEquation(const ComplexNumber& a, const ComplexNumber& b) : LineEquation(static_cast<Point>(a), static_cast<Point>(b)) { }

LineEquation::LineEquation(const Point& a, const Point& b)
{
    if (a == b
        || std::isinf(a.X())
        || std::isinf(b.X())
        || std::isinf(a.Y())
        || std::isinf(b.Y()))
        throw std::runtime_error("Cannot create line from 2 equal points, or coordinates incorrect (a.e. Inf)");

    _pointA = a, _pointB = b;

    yDiff = _pointB.Y() - _pointA.Y();
    xDiff = _pointB.X() - _pointA.X();
    type = (xDiff == 0)
        ? LineType::CONST_X
        : ((yDiff == 0) ? LineType::CONST_Y : LineType::NORMAL);

    initByLineType();
    _inited = true;
    return;
}
