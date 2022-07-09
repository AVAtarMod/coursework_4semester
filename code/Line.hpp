#ifndef LINE_LIB
#define LINE_LIB

#include "Point.hpp"
#include <tuple>

/**
 * @brief Represents line by equation 'y = kx + b'
 */
class Line {
private:
    double k, b;

public:
    Line(double k, double b) : k(k), b(b) { }
    Line(std::pair<Point, Point> pair);

    double y(double x) const { return k * x + b; }
    bool isPointBelongsLine(Point point);
};

#endif // LINE_LIB
