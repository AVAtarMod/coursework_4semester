#include "Line.hpp"

Line::Line(std::pair<Point, Point> pair){
    k = 0;
    b = 0;
}

bool Line::isPointBelongsLine(Point point){
    return y(point.X) == point.Y;
}
