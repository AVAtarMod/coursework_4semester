#include "Circle.hpp"

#include "Line.hpp"
#include "functions.hpp"
#include <cmath>
#include <exception>

Circle::Circle(const Point& center, double radius)
{
   bool isValidInput = !std::isinf(radius) && !Point::isAtInfinity(center);
   if (!isValidInput)
      throw std::runtime_error(
        "Cannot construct the circle for infinity radius or center");

   _center = center;
   _radius = radius;
}
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

bool Circle::isBelongs(const Point& a) const
{
   return almost_equal(power(a.X() - _center.X(), 2) +
                         power(a.Y() - _center.Y(), 2),
                       power(_radius, 2));
}

bool Circle::isBelongs(const Point& a, int8_t dds) const
{
   if (dds < 0)
      throw std::invalid_argument(
        "Circle::isBelongs: cannot set negative precision");
        
   return floor(power(a.X() - _center.X(), 2) + power(a.Y() - _center.Y(), 2),
                dds) == floor(power(_radius, 2), dds);
}

std::pair< double, double > Circle::y(double x) const
{
   const double value =
     std::sqrt(power(_radius, 2) - power(x - _center.X(), 2));
   return { _center.Y() + value, _center.Y() - value };
}
std::pair< double, double > Circle::x(double y) const
{
   const double value =
     std::sqrt(power(_radius, 2) - power(y - _center.Y(), 2));
   return { _center.X() + value, _center.X() - value };
}

Circle::~Circle()
{
   _center.~Point();
}
