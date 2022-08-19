#include "LineSegment.hpp"
#include "functions.hpp"
#include "tfunctions.hpp"

inline void task3::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Compare with precision up to comparePrecision digits after decimal
    * separator.
    */
   const uint8_t comparePrecision = 1;
   const int numbersCount = 4;

   ComplexNumber numbers[numbersCount];
   const std::string labels[numbersCount] { "A", "B", "C", "D" };
   // clang-format off

   // References for readability
   ComplexNumber  &a = numbers[0],
                  &b = numbers[1], 
                  &c = numbers[2],
                  &d = numbers[3];
   // clang-format on

   returnCode = 0;
   task1::readTriangleFromUser(numbers, labels, options, returnCode);
   if (returnCode != EXIT_SUCCESS)
      return;

   const LineSegment AB { a.toPoint(), b.toPoint() },
     AC { a.toPoint(), c.toPoint() }, BC { b.toPoint(), c.toPoint() };
   const std::pair< Point, Point >& pair = AC.move(AB).getEndpoints();
   d = (pair.first == b.toPoint()) ? pair.second : pair.first;

   const LineSegment BD { b.toPoint(), d.toPoint() },
     CD { c.toPoint(), d.toPoint() }, AD { a.toPoint(), d.toPoint() };

   // Check 'AD^2 + BC^2 = AB^2 + CD^2 + BD^2 + AC^2'
   if (areEqual(power(AD.length(), 2) + power(BC.length(), 2),
                power(AB.length(), 2) + power(CD.length(), 2) +
                  power(BD.length(), 2) + power(AC.length(), 2),
                static_cast< int8_t >(comparePrecision))) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "AD^2 + BC^2 != AB^2 + CD^2 + BD^2 + AC^2.\n";
}
