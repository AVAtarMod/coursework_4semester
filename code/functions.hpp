#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include "ComplexNumber.hpp"
#include <limits>
#include <cmath>
#include <tuple>

using lineSegment_t = std::pair<ComplexNumber, ComplexNumber>;

/**
 * @brief Intersect of 2 line segments
 * @return ComplexNumber, intersection point of lines
 */
ComplexNumber intersect(lineSegment_t first, lineSegment_t second);

bool isPointBelongsSegment(lineSegment_t segment, ComplexNumber point);

void Task1_ReadNumbersFromUser(ComplexNumber arr[5], const std::string labels[5]);

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
