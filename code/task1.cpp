#include "tfunctions.hpp"

#include "Circle.hpp"
#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "functions.hpp"

inline void task1::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Numbers differs lesser than comparePrecision
    */
   const double comparePrecision = 0.1;
   /**
    * @brief Amount digits after decimal separator
    */
   const int8_t roundPrecision = 2;
   returnCode = 0;
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

   readTriangleFromUser(numbers, labels, options, returnCode);
   if (returnCode != EXIT_SUCCESS)
      return;

   Circle circle { static_cast< Point >(a),
                   static_cast< Point >(b),
                   static_cast< Point >(c) };

   o = ComplexNumber::floor({ circle.center() }, roundPrecision);

   const Line AB { a, b };
   const Line p = Line::makePerpendicular(AB, static_cast< Point >(o));
   const Point i = Line::intersect(AB, p);

   switch (p.getType()) {
      case LineType::CONST_X:
         d = Point { p.x(randY), -static_cast< Point >(o).Y() + 2 * i.Y() };
         break;
      case LineType::CONST_Y:
         d = Point { -static_cast< Point >(o).X() + 2 * i.X(), p.y(randX) };
         break;
      case LineType::NORMAL:
         d = Point { -static_cast< Point >(o).X() + 2 * i.X(),
                     -static_cast< Point >(o).Y() + 2 * i.Y() };
         break;
   }
   d = ComplexNumber::floor(d, roundPrecision);

   const LineSegment sCD { static_cast< Point >(c), static_cast< Point >(d) },
     sAC { static_cast< Point >(a), static_cast< Point >(c) },
     sBC { static_cast< Point >(b), static_cast< Point >(c) },
     sAB { static_cast< Point >(a), static_cast< Point >(b) };

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
