#ifndef POINT_LIB
#define POINT_LIB

class Point {
private:
    double _x, _y;

public:
    Point(double x, double y) : _x(x), _y(y), X(_x), Y(_y) {};
    const double& X;
    const double& Y;
    ~Point();
};

#endif // POINT_LIB
