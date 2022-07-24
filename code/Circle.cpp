#include "Circle.hpp"

#include <exception>

#include "Line.hpp"

Circle::Circle(const Point& a, const Point& b, const Point& c)
{
   if (Line(a, b).isBelongs(c))
      throw std::runtime_error(
        "Cannot construct the circle by 3 points. They belongs same line");

   /**
    * @brief Calculted coordinates of circle center
    * @see https://en.wikipedia.org/wiki/Ellipse#Circles
    */
   double X, Y;
   X = -1 / 2 *
       (a.Y() *
        ((b.X() * b.X() + b.Y() * b.Y()) - (c.X() * c.X() + c.Y() * c.Y())));
}

Circle::~Circle()
{
   center.~Point();
}
