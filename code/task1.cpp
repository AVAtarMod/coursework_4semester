#include "tfunctions.hpp"

#include "Circle.hpp"
#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "functions.hpp"

/**
 * @brief Function that solve task #1.
 *
 * @param returnCode number, which represents a error status. 0 - no error
 * ocurred, 1 - otherwise.
 * @param options struct, which represents options. Usually useful for setting
 * the output format.
 */
inline void task1::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Numbers should differs lesser than comparePrecision
    */
   const double comparePrecision = 0.1;
   /**
    * @brief Amount digits after decimal separator
    */
   const int8_t roundPrecision = 2;
   returnCode = 0;
   /**
    * @brief The amount of numbers.
    */
   const int numbersCount = 5;
   /**
    * @brief Random constant values. They need for get x() or y() values of
    * lines kind of 'y = const' or 'x = const'
    */
   const int &randX = numbersCount, &randY = numbersCount;
   ComplexNumber numbers[numbersCount];
   const std::string labels[numbersCount] { "A", "B", "C", "D", "O" };
   // clang-format off

   // References for readability
   ComplexNumber  &a = numbers[0],
                  &b = numbers[1], 
                  &c = numbers[2],
                  &d = numbers[3],
                  &o = numbers[4];
   // clang-format on

   /**
    * @brief Reading points from user. This function assign values to numbers
    * array.
    */
   readTriangleFromUser(numbers, labels, options, returnCode);
   if (returnCode != EXIT_SUCCESS)
      return;

   Circle circle { a.toPoint(), b.toPoint(), c.toPoint() };

   o = ComplexNumber::round({ circle.center() }, roundPrecision);

   const Line AB { a, b };
   const Line p = Line::makePerpendicular(AB, o.toPoint());
   const Point i = Line::intersect(AB, p);

   /**
    * @brief Calculating d (it depends line type of p)
    */
   switch (p.getType()) {
      case LineType::CONST_X:
         d = Point { p.x(randY), -o.toPoint().Y() + 2 * i.Y() };
         break;
      case LineType::CONST_Y:
         d = Point { -o.toPoint().X() + 2 * i.X(), p.y(randX) };
         break;
      case LineType::NORMAL:
         d =
           Point { -o.toPoint().X() + 2 * i.X(), -o.toPoint().Y() + 2 * i.Y() };
         break;
   }
   d = ComplexNumber::round(d, roundPrecision);

   const LineSegment sCD { c.toPoint(), d.toPoint() },
     sAC { a.toPoint(), c.toPoint() }, sBC { b.toPoint(), c.toPoint() },
     sAB { a.toPoint(), b.toPoint() };

   // Check 'CD^2 = R^2 + AC^2 + BC^2 - AB^2'
   const double lhs = power(sCD.length(), 2);
   const double rhs = power(circle.radius(), 2) + power(sAC.length(), 2) +
                      power(sBC.length(), 2) - power(sAB.length(), 2);
   if (areEqual(lhs, rhs, comparePrecision)) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "CD^2 != R^2 + AC^2 + BC^2 - AB^2.\n";
}
