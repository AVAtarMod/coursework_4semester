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
    void finishInit(const LineEquation& initedEquation);

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
