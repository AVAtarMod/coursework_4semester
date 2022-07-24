#include "ComplexNumber.hpp"
#include "functions.hpp"

inline void task1::solve(int& returnCode, const ProgramOptions& options)
{
   returnCode = 0;
   const int numbersCount = 5;
   ComplexNumber numbers[numbersCount];
   const std::string labels[numbersCount] = { "A", "B", "C", "D", "O" };
   // References for readability
   ComplexNumber &a = numbers[0], &b = numbers[1], &c = numbers[2],
                 &d = numbers[3], &o = numbers[4];

   readTriangleFromUser(numbers, labels, options, returnCode);
   if (returnCode != EXIT_FAILURE)
      return;

   if (1) {
      printMessage(options, "Computed coordinates:\n");
      for (size_t i = 0; i < numbersCount; i++) {
         printMessage(options, "%N\n", &numbers[i]);
      }
   } else
      std::cerr
        << "The computed points M,N,P is not belong to the same line, so the Guss's theorem is not true.\n";
}
