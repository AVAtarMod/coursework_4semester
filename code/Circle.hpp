#ifndef CIRCLE_LIB
#define CIRCLE_LIB

#include "Point.hpp"

class Circle
{
  private:
   Point _center;
   double _radius;

  public:
   Circle(const Point& a, const Point& b, const Point& c);

   Point center() const { return _center; }
   const double& radius() const { return _radius; }

   ~Circle();
};

#endif // CIRCLE_LIB
