#ifndef LINESEGMENT_LIB
#define LINESEGMENT_LIB

#include "Line.hpp"

class LineSegment
{
  private:
   Line _line;
   Point _endpoints[2];

  public:
   LineSegment(const Point& a, const Point& b);
   LineSegment(const Line& l, const Point endpoints[2]);

   std::pair< Point, Point > getEndpoints();
   double length() const;

   ~LineSegment();
};

#endif // LINESEGMENT_LIB
