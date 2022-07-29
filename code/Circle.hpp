#ifndef COURSEWORK_4_1_CIRCLE_HPP
#define COURSEWORK_4_1_CIRCLE_HPP

#include "Point.hpp"
#include <utility>
#include <cstdint>

class Circle
{
  private:
   Point _center;
   double _radius;

  public:
   Circle(const Point& center, double radius);
   Circle(const Point& a, const Point& b, const Point& c);

   Point center() const { return _center; }
   const double& radius() const { return _radius; }

   std::pair< double, double > y(double x) const;
   std::pair< double, double > x(double y) const;

   bool isBelongs(const Point& a) const;
   /**
    * @brief Does check is Point belongs to this circle with precision up to dds
    * digits after decimal separator
    *
    * @param a A point that need to check
    * @param dds Compare precision - digits after decimal separator
    */
   bool isBelongs(const Point& a, int8_t dds ) const;

   ~Circle();
};

#endif // COURSEWORK_4_1_CIRCLE_HPP
