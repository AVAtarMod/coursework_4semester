#ifndef COURSEWORK_4_1_CIRCLEARC_HPP
#define COURSEWORK_4_1_CIRCLEARC_HPP

#include "Circle.hpp"

class CircleArc
{
  private:
   const Circle& _circle;
   Point _a, _b, _between;

  public:
   /**
    * @brief Construct a new circle arc by source circle and 3 points. All points should to be at the circle and not equal each other.
    *
    * @param circle Source circle
    * @param a Begin point of the arc
    * @param b End point of the arc
    * @param betweenAB A point between a,b. Needed for unambiguous constructing
    * resulted arc.
    */
   CircleArc(const Circle& circle, const Point& a, const Point& b,
             const Point& betweenAB);

   static Point middle(const CircleArc& arc);

   ~CircleArc();
};

#endif // COURSEWORK_4_1_CIRCLEARC_HPP
