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
   } while (!circle.isBelongs(static_cast< Point >(a), comparePrecision) ||
            !circle.isBelongs(static_cast< Point >(b), comparePrecision) ||
            !circle.isBelongs(static_cast< Point >(n), comparePrecision));

   m = CircleArc(circle,
                 static_cast< Point >(a),
                 static_cast< Point >(b),
                 static_cast< Point >(t),
                 useApproximation)
         .middle();

   const LineSegment AM { static_cast< Point >(a), static_cast< Point >(m) },
     MN { static_cast< Point >(m), static_cast< Point >(n) },
     AN { static_cast< Point >(a), static_cast< Point >(n) },
     BN { static_cast< Point >(b), static_cast< Point >(n) };

   // Check '|AM^2 - MN^2| = AN * BN'
   if (std::abs(power(AM.length(), 2) - power(MN.length(), 2)) ==
       AN.length() * BN.length()) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "|AM^2 - MN^2| != AN * BN.\n";
}
