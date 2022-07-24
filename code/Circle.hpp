#ifndef CIRCLE_LIB
#define CIRCLE_LIB

#include "Point.hpp"

class Circle
{
  private:
   Point center;
   unsigned int radius;

  public:
   Circle(const Point& a, const Point& b, const Point& c);
   ~Circle();
};

#endif // CIRCLE_LIB
