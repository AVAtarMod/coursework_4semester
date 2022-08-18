#include "Circle.hpp"
#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "Quadrilateral.hpp"
#include "functions.hpp"
#include "tfunctions.hpp"

inline void task6::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Compare with precision up to comparePrecision
    */
   const double comparePrecision = 0.1;
   const int numbersCount = 5;
   const ComplexNumber half(1.0 / 2.0, 1.0 / 2.0);
   LineSegment P1P2, T1T2;

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

   task6::readNumbersFromUser(numbers, labels, options, returnCode);

   const Line AD(a, d), BC(b, c);
   Circle circle(a.toPoint(), b.toPoint(), c.toPoint());

   o = circle.center();

   // Check AB^2 + CD^2 = AC^2 + BD^2 = (2OB)^2
   double first = power(LineSegment(a.toPoint(), b.toPoint()).length(), 2) +
                  power(LineSegment(c.toPoint(), d.toPoint()).length(), 2);
   double second = power(LineSegment(a.toPoint(), c.toPoint()).length(), 2) +
                   power(LineSegment(b.toPoint(), d.toPoint()).length(), 2);
   double third = power(2 * LineSegment(o.toPoint(), b.toPoint()).length(), 2);
   if (areEqual(first, second, comparePrecision) &&
       areEqual(second, third, comparePrecision)) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "AD is not perpendicular to CB\n";
}
