#include "ComplexNumber.hpp"
#include "LineSegment.hpp"
#include "Quadrilateral.hpp"
#include "functions.hpp"
#include "tfunctions.hpp"

inline void task7::solve(int& returnCode, const ProgramOptions& options)
{
   /**
    * @brief Compare with precision up to comparePrecision digits after decimal
    * separator.
    */
   const double comparePrecision = 0.1;
   const int numbersCount = 9;
   const ComplexNumber half(1.0 / 2.0, 1.0 / 2.0);
   LineSegment P1P2, T1T2;

   ComplexNumber numbers[numbersCount];
   const std::string labels[numbersCount] { "A",  "B",  "C",  "D", "O",
                                            "P1", "P2", "T1", "T2" };
   // clang-format off

   // References for readability
   ComplexNumber  &a = numbers[0],
                  &b = numbers[1], 
                  &c = numbers[2],
                  &d = numbers[3],
                  &o = numbers[4],
                  &p_1 = numbers[5],
                  &p_2 = numbers[6],
                  &t_1 = numbers[7],
                  &t_2 = numbers[8];
   // clang-format on

   do {
      try {
         task7::readNumbersFromUser(numbers, labels, options, returnCode);
         Quadrilateral tmp(static_cast< Point >(a),
                           static_cast< Point >(b),
                           static_cast< Point >(c),
                           static_cast< Point >(d));
      } catch (const std::invalid_argument&) {
         std::cerr
           << "Cannot construct quadrilateral by a,b,c,d. You should enter valid points.\n";
         continue;
      }
      t_1 = (a + b) * half, t_2 = (c + d) * half;
      T1T2 = LineSegment(static_cast< Point >(t_1), static_cast< Point >(t_2));

      p_1 = (a + c) * half, p_2 = (b + d) * half;
      P1P2 = LineSegment(static_cast< Point >(p_1), static_cast< Point >(p_2));
   } while (!areEqual(P1P2.length(), T1T2.length(), comparePrecision));

   const Line AD(a, d), BC(b, c);
   o = Line::intersect(AD, BC);

   // Check AD is perpendicular to BC
   if (AD.isPerpendicular(BC, comparePrecision)) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersCount);
   } else
      std::cerr << "AD is not perpendicular to BC\n";
}
