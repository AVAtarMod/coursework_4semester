#include "LineSegment.hpp"

#include "functions.hpp"
#include "tfunctions.hpp"
#include <cmath>

LineSegment::LineSegment(const Point& a, const Point& b) :
  _line(a, b), _endpoints { a, b }
{
}

LineSegment::LineSegment(const Line& l, const Point endpoints[2]) :
  _line(l), _endpoints { endpoints[0], endpoints[1] }
{
   bool isPointsCorrect =
     l.isBelongs(endpoints[0]) && l.isBelongs(endpoints[1]);
   if (!isPointsCorrect)
      throw std::runtime_error(
        "Cannot construct line segment: endpoints not on soource line");
}

std::pair< Point, Point > LineSegment::getEndpoints()
{
   return std::pair< Point, Point > { _endpoints[0], _endpoints[1] };
}
double LineSegment::length() const
{
   // ((a_x-b_x)^2+(a_y-b_y)^2)^(1/2)
   return sqrt(power(_endpoints[1].X() - _endpoints[0].X(), 2) +
               power(_endpoints[1].Y() - _endpoints[0].Y(), 2));
}

LineSegment::~LineSegment()
{
   /**
    * @brief Cleanup of points and line
    */
   _line.~Line();
   _endpoints[0].~Point();
   _endpoints[1].~Point();
}
