/**
 * @file functions.hpp
 * @author Grigory Stupnikov (stud128245@vyatsu.ru)
 * @brief
 * @version 0.1
 * @date 2022-07-14
 *
 * @copyright Copyright © 2022 Grigory Stupnikov. All rights reserved. Licensed under GNU GPLv3. See https://opensource.org/licenses/GPL-3.0.
 */
#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include "ComplexNumber.hpp"
#include <cmath>
#include <limits>
#include <tuple>

using clineSegment_t = std::pair<ComplexNumber, ComplexNumber>;

/**
 * @brief Intersect of 2 line segments
 * @return ComplexNumber, intersection point of lines
 */
ComplexNumber intersect(clineSegment_t first, clineSegment_t second);

bool isPointBelongsSegment(clineSegment_t segment, ComplexNumber point);

namespace task1 {
void ReadNumbersFromUser(ComplexNumber arr[5], const std::string labels[5]);
void solve();
} // namespace task1

namespace task5 {
void ReadNumbersFromUser(ComplexNumber arr[5], const std::string labels[5]);
void solve();
} // namespace task5

template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
        // unless the result is subnormal
        || std::fabs(x - y) < std::numeric_limits<T>::min();
}

#endif // FUNCTIONS_LIB
