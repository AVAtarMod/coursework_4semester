#include "Circle.hpp"

#include "Line.hpp"
#include "functions.hpp"
#include <cmath>
#include <exception>

Circle::Circle(const Point& a, const Point& b, const Point& c)
{
   if (Line(a, b).isBelongs(c))
      throw std::runtime_error(
        "Cannot construct the circle by 3 points. They belongs same line");

   /**
    * @brief Calculted coordinates of circle _center
    * @see https://en.wikipedia.org/wiki/Ellipse#Circles
    */
   double X, Y;
   const double &aX = a.X(), &aY = a.Y(), &bX = b.X(), &bY = b.Y(), &cX = c.X(),
                &cY = c.Y();
   const double denominator =
     (aX * (bY - cY) + bX * (cY - aY) + cX * (aY - bY));
     
   X = (-1.0 / 2.0) *
       (aY * ((power(bX, 2) + power(bY, 2)) - (power(cX, 2) + power(cY, 2))) +
        bY * ((power(cX, 2) + power(cY, 2)) - (power(aX, 2) + power(aY, 2))) +
        cY * ((power(aX, 2) + power(aY, 2)) - (power(bX, 2) + power(bY, 2)))) /
       denominator;
   Y = (1.0 / 2.0) *
       (aX * ((power(bX, 2) + power(bY, 2)) - (power(cX, 2) + power(cY, 2))) +
        bX * ((power(cX, 2) + power(cY, 2)) - (power(aX, 2) + power(aY, 2))) +
        cX * ((power(aX, 2) + power(aY, 2)) - (power(bX, 2) + power(bY, 2)))) /
       denominator;

   _center = Point(X, Y);
   _radius = sqrt(power(aX - _center.X(), 2) + power(aY - _center.Y(), 2));
}

Circle::~Circle()
{
   _center.~Point();
}
