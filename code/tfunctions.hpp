/**
 * @file tfunctions.hpp
 * @author Grigory Stupnikov (stud128245@vyatsu.ru)
 * @brief
 * @version 0.1
 * @date 2022-07-14
 *
 * @copyright Copyright © 2022 Grigory Stupnikov. All rights reserved. Licensed
 * under GNU GPLv3. See https://opensource.org/licenses/GPL-3.0.
 */
#ifndef COURSEWORK_4_1_TFUNCTIONS_HPP
#define COURSEWORK_4_1_TFUNCTIONS_HPP

#include "ComplexNumber.hpp"

#include <cmath>
#include <limits>
#include <tuple>

using clineSegment_t = std::pair< ComplexNumber, ComplexNumber >;

struct ProgramOptions
{
   enum OutputStyle
   {
      UNIX, // Plain, no output except result, useful for debug
      RICH  // Plain, print messages to user
   } outputStyle = RICH;
};

/**
 * @brief Intersect of 2 line segments
 * @return ComplexNumber, intersection point of lines
 */
ComplexNumber intersect(const clineSegment_t& first, clineSegment_t second);

bool isPointBelongsSegment(const clineSegment_t& segment, ComplexNumber point);

clineSegment_t perpendicular(const clineSegment_t& to, ComplexNumber from);
/**
 * @brief Print message. It prints only numbers if options.outputStyle == UNIX.
 * Passing non null-terminated string is UB, don't do this!
 * Supported format specifiers:
 * %N - complex number (ComplexNumber*)
 * %s - string (const char*)
 * @param ... data to print
 */
void printMessage(const ProgramOptions& options, const char* format, ...);

void printNumbers(const ProgramOptions& options, const ComplexNumber numbers[],
                  const std::string labels[], const size_t amount);

namespace task1 {
   void readTriangleFromUser(ComplexNumber arr[3], const std::string labels[3],
                             const ProgramOptions& options, int& returnCode);
   void solve(int& returnCode, const ProgramOptions& options);
}

namespace task5 {
   void readNumbersFromUser(ComplexNumber arr[5], const std::string labels[5],
                            const ProgramOptions& options, int& returnCode);

   void solve(int& returnCode, const ProgramOptions& options);
}

template< class T >
typename std::enable_if< !std::numeric_limits< T >::is_integer, bool >::type almost_equal(
  T x, T y, int ulp)
{
   // the machine epsilon has to be scaled to the magnitude of the values used
   // and multiplied by the desired precision in ULPs (units in the last place)
   return std::fabs(x - y) <=
            std::numeric_limits< T >::epsilon() * std::fabs(x + y) * ulp
          // unless the result is subnormal
          || std::fabs(x - y) < std::numeric_limits< T >::min();
}

#endif // COURSEWORK_4_1_TFUNCTIONS_HPP