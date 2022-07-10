#include "Line.hpp"
#include "functions.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

struct EquationDataFromPoints {
    Point A, B;
    double eqK, eqB, xConst, yConst;
    bool inited = false;
} tmp;

void initTmpFromPoints(const Point& a, const Point& b)
{
    if (a == b || std::isinf(a.X()) || std::isinf(a.Y()) || std::isinf(b.X()) || std::isinf(b.Y()))
        throw std::runtime_error("Cannot create line from 2 equal points, or coordinates incorrect (a.e. Inf)");

    if (!tmp.inited || tmp.A != a || tmp.B != b) {
        tmp.A = a, tmp.B = b;

        double yDiff = tmp.B.Y() - tmp.A.Y();
        double xDiff = tmp.B.X() - tmp.A.X();

        int lineType = (xDiff == 0) ? 0 : ((yDiff == 0) ? 1 : 2);
        switch (lineType) {
        case 0:
            // Y may be any, x = const
            tmp.eqK = 0;
            tmp.eqB = std::numeric_limits<double>::infinity();
            tmp.xConst = tmp.B.X();
            break;
        case 1:
            // X may be any, y = const
            tmp.eqK = 0;
            tmp.eqB = 0;
            tmp.yConst = tmp.B.Y();
            break;
        case 2:
            // Normal line, y = kx + b
            tmp.eqK = yDiff / xDiff;
            tmp.eqB = (-tmp.A.X() * yDiff + tmp.A.Y() * xDiff) / xDiff;
            break;
        default:
            break;
        }

        tmp.inited = true;
    }

    return;
}

double Line::getKFromPoints(const Point& a, const Point& b)
{
    initTmpFromPoints(a, b);
    return tmp.eqK;
}
double Line::getBFromPoints(const Point& a, const Point& b)
{
    initTmpFromPoints(a, b);
    return tmp.eqB;
}

Line::Line(std::pair<Point, Point> pair)
    : _k(getKFromPoints(pair.first, pair.second)),
      _b(getBFromPoints(pair.first, pair.second))
{
    if (std::isinf(_b)) {
        _type = LineType::CONST_X;
        _x = tmp.xConst;
    } else if (_k == 0) {
        _type = LineType::CONST_Y;
        _y = tmp.yConst;
    } else
        _type = LineType::NORMAL;
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
