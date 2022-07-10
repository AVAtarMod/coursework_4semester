#ifndef POINT_LIB
#define POINT_LIB

class Point {
private:
    double _x, _y;

public:
    Point(double x = 0, double y = 0) : _x(x), _y(y) {};

    bool operator==(const Point& a) const { return X() == a.X() && Y() == a.Y(); }
    bool operator!=(const Point& a) const { return !(*this == a); }

    const double& X() const { return _x; }
    const double& Y() const { return _y; }
};

#endif // POINT_LIB
