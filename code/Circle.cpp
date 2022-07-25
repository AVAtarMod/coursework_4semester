#include "Circle.hpp"

#include "Line.hpp"
#include <cmath>
#include <exception>
#include "functions.hpp"

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
   X = (-1 / 2) *
       (aY * ((pow(bX, 2) + pow(bY, 2)) - (pow(cX, 2) + pow(cY, 2))) +
        bY * ((pow(cX, 2) + pow(cY, 2)) - (pow(aX, 2) + pow(aY, 2))) +
        cY * ((pow(aX, 2) + pow(aY, 2)) - (pow(bX, 2) + pow(bY, 2)))) /
       denominator;
   Y = (1 / 2) *
       (aX * ((pow(bX, 2) + pow(bY, 2)) - (pow(cX, 2) + pow(cY, 2))) +
        bX * ((pow(cX, 2) + pow(cY, 2)) - (pow(aX, 2) + pow(aY, 2))) +
        cX * ((pow(aX, 2) + pow(aY, 2)) - (pow(bX, 2) + pow(bY, 2)))) /
       denominator;

   _center = Point(X, Y);
   _radius = sqrt(pow(aX - _center.X(), 2) + pow(aY - _center.Y(), 2));
}

Circle::~Circle()
{
   _center.~Point();
}
