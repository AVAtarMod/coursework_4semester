#include "tfunctions.hpp"

#include "Circle.hpp"
#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "functions.hpp"

inline void task1::solve(int& returnCode, const ProgramOptions& options)
{
   returnCode = 0;
   const int numbersCount = 5;
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
   if (returnCode != EXIT_FAILURE)
      return;

   Circle circle { static_cast< Point >(a),
                   static_cast< Point >(b),
                   static_cast< Point >(c) };

   o = { circle.center() };
   clineSegment_t segment =
     LineSegment::makePerpendicular(Line(a, b), static_cast< Point >(o))
       .getEndpoints();

   d = (segment.first == o) ? segment.second : segment.first;

   const LineSegment CD { static_cast< Point >(c), static_cast< Point >(d) },
     AC { static_cast< Point >(a), static_cast< Point >(c) },
     BC { static_cast< Point >(b), static_cast< Point >(c) },
     AB { static_cast< Point >(a), static_cast< Point >(b) };

   // Check 'CD^2 = R^2 + AC^2 + BC^2 - AB^2'
   if (power(CD.length(), 2) ==
       power(circle.radius(), 2) + power(AC.length(), 2) +
         power(BC.length(), 2) - power(AB.length(), 2)) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "CD^2 != R^2 + AC^2 + BC^2 - AB^2.\n";
}
