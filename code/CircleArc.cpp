#include "CircleArc.hpp"

#include "functions.hpp"
#include <cmath>
#include <stdexcept>

void CircleArc::initByExactValues(const Point& a, const Point& b,
                                  const Point& betweenAB)
{
   bool isValidInput = _circle.isBelongs(a) && _circle.isBelongs(b) &&
                       _circle.isBelongs(betweenAB) && a != b && b != betweenAB;
   if (!isValidInput)
      throw std::invalid_argument(
        "CircleArc: Cannot construct. One or more points not at the circle or points equal");

   Angle angles[3] { _circle.getAngle(a),
                     _circle.getAngle(b),
                     _circle.getAngle(betweenAB) };

   if (angles[0].degrees() < angles[1].degrees()) {
      _boundaries[0] = angles[0];
      _boundaries[1] = angles[1];
   } else {
      _boundaries[0] = angles[1];
      _boundaries[1] = angles[0];
   }
   _boundaries[2] = angles[2];
}

CircleArc::CircleArc(const Circle& circle, const Point& a, const Point& b,
                     const Point& betweenAB) :
  _circle(circle)
{
   initByExactValues(a, b, betweenAB);
}

CircleArc::CircleArc(const Circle& circle, const Point& a, const Point& b,
                     const Point& betweenAB, bool approximate) :
  _circle(circle)
{
   if (approximate) {
      initByExactValues(_circle.getExactPoint(a),
                        _circle.getExactPoint(b),
                        _circle.getExactPoint(betweenAB));
   } else
      initByExactValues(a, b, betweenAB);
}

bool CircleArc::isBelongs(const Point& point) const
{
   Point normalized { point.X() - _circle.center().X(),
                      point.Y() - _circle.center().Y() };
}

Point CircleArc::middle() const
{
   const int comparePrecision = 100;
   
}

CircleArc::~CircleArc()
{
   _boundaries[0].~Angle();
   _boundaries[1].~Angle();
}
