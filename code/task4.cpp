#include "ComplexNumber.hpp"
#include "Line.hpp"
#include "tfunctions.hpp"

inline void task4::solve(int& returnCode, const ProgramOptions& options)
{
   returnCode = 0;
   const int numbersAmount = 9;
   ComplexNumber numbers[numbersAmount];
   const std::string labels[numbersAmount] { "A",  "B", "C", "A1", "B1",
                                             "C1", "M", "N", "P" };
   // clang-format off
   
   // References for readability
   ComplexNumber  &a = numbers[0],
                  &b = numbers[1],
                  &c = numbers[2],
                  &a1 = numbers[3],
                  &b1 = numbers[4],
                  &c1 = numbers[5],
                  &m = numbers[6],
                  &n = numbers[7],
                  &p = numbers[8];
   // clang-format on
   readNumbersFromUser(numbers, labels, options, returnCode);
   if (returnCode != EXIT_SUCCESS)
      return;

   std::pair< ComplexNumber, ComplexNumber > pairs[2] { { a, b }, { b1, a1 } };

   c1 = intersect(pairs[0], pairs[1]);
   m = Point::middle(a.toPoint(), a1.toPoint());
   n = Point::middle(b.toPoint(), b1.toPoint());
   p = Point::middle(c.toPoint(), c1.toPoint());

   if (Line::isOnSameLine(m, n, p)) {
      printMessage(options, "Computed coordinates:\n");
      printNumbers(options, numbers, labels, numbersAmount);
   } else
      std::cerr
        << "The computed points M,N,P is not belong to the same line.\n";
}
