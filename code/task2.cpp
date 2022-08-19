#include "Circle.hpp"
#include "CircleArc.hpp"
#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "functions.hpp"
#include "tfunctions.hpp"

inline void task2::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Compare with precision up to comparePrecision digits after decimal
    * separator.
    */
   const uint8_t comparePrecision = 1;
   const int numbersCount = 5;
   const uint32_t circleRadius = 1;
   const bool useApproximation = true;

   ComplexNumber numbers[numbersCount];
   const std::string labels[numbersCount] { "A", "B", "N", "T", "M" };
   // clang-format off

   // References for readability
   ComplexNumber  &a = numbers[0],
                  &b = numbers[1], 
                  &n = numbers[2],
                  &t = numbers[3],
                  &m = numbers[4];
   // clang-format on
   const Circle circle { Point::zero(), circleRadius };

   returnCode = 0;
   do {
      readNumbersFromUser(numbers, labels, options, returnCode);
      if (returnCode != EXIT_SUCCESS)
         return;
   } while (!circle.isBelongs(a.toPoint(), comparePrecision) ||
            !circle.isBelongs(b.toPoint(), comparePrecision) ||
            !circle.isBelongs(n.toPoint(), comparePrecision));

   m =
     CircleArc(circle, a.toPoint(), b.toPoint(), t.toPoint(), useApproximation)
       .middle();

   const LineSegment AM { a.toPoint(), m.toPoint() },
     MN { m.toPoint(), n.toPoint() }, AN { a.toPoint(), n.toPoint() },
     BN { b.toPoint(), n.toPoint() };

   // Check '|AM^2 - MN^2| = AN * BN'
   if (areEqual(std::abs(power(AM.length(), 2) - power(MN.length(), 2)),
                AN.length() * BN.length(),
                static_cast< int8_t >(comparePrecision))) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "|AM^2 - MN^2| != AN * BN.\n";
}
