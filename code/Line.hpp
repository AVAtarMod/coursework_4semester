#ifndef LINE_LIB
#define LINE_LIB

#include "ComplexNumber.hpp"
#include "Point.hpp"
#include <tuple>

enum class LineType {
    CONST_Y, // y = const
    CONST_X, // x = const
    NORMAL // y = kx + b
};

/**
 * @brief This namespace contain implentation details only , don't use it!
 */
namespace implementation
{
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
} // namespace implementation

/**
 * @brief Represents line by equation 'y = kx + b'
 */
class Line {
private:
    double _k, _b;

    /**
     * @brief Defines y or x constant value if _type is CONST_X or CONST_Y. This is reference for memory optimization.
     */
    double &_x = _b, &_y = _k;
    LineType _type;

    static double getKFromPoints(const Point& a, const Point& b);
    static double getBFromPoints(const Point& a, const Point& b);
    void finishInit(const implementation::LineEquation& initedEquation);

public:
    Line(double k, double b) : _k(k), _b(b) { }
    Line(const std::pair<Point, Point>& pair);
    Line(const Point& first, const Point& second) : Line(std::make_pair(first, second)) { }
    
    /**
     * @brief Construct a new Line object (algorithm is same as for the two Points)
     */
    Line(const ComplexNumber& first, const ComplexNumber& second);

    LineType getType() const { return _type; }

    double y(double x) const;
    double x(double y) const;

    const double& K() const { return _k; }
    const double& B() const { return _b; }

    bool isInX(double x) const;
    bool isInY(double y) const;

    bool isBelongs(Point point);
};

#endif // LINE_LIB
