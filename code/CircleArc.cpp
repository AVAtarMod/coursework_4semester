#include "CircleArc.hpp"

#include <stdexcept>

CircleArc::CircleArc(const Circle& circle, const Point& a, const Point& b,
                     const Point& betweenAB) :
  _circle(circle)
{
   bool isValidInput = _circle.isBelongs(a) && _circle.isBelongs(b) &&
                       _circle.isBelongs(betweenAB) && a != b && b != betweenAB;
   if (!isValidInput)
      throw std::invalid_argument(
        "CircleArc: Cannot construct. One or more points not at the circle or points equal");

   _a = a;
   _b = b;
   _between = betweenAB;
}

Point CircleArc::middle(const CircleArc& arc)
{
   const double arcXMin = std::min(arc._a.X(), arc._b.X()),
                arcXMax = std::max(arc._a.X(), arc._b.X());
   const double x = arcXMin + (arcXMax - arcXMin) / 2;
   auto yRaw = arc._circle.y(x);
   double y;
   if (arc._a.X() == -arc._b.X() || yRaw.first != yRaw.second) {
      // y must be closer to _between by Y
      y = (std::abs(yRaw.first - arc._between.Y()) <
           std::abs(yRaw.second - arc._between.Y()))
            ? yRaw.first
            : yRaw.second;
   } else if (yRaw.first == yRaw.second) {
      y = yRaw.first;
   }
   return Point(x, y);
}

CircleArc::~CircleArc()
{
   _a.~Point();
   _b.~Point();
   _between.~Point();
}
