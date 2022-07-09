#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include "ComplexNumber.hpp"
#include "Line.hpp"

#include <tuple>

using lineSegment_t = std::pair<ComplexNumber, ComplexNumber>;

/**
 * @brief Intersect of 2 line segments
 * @return ComplexNumber, intersection point of lines
 */
ComplexNumber intersect(lineSegment_t first, lineSegment_t second);

bool isPointBelongsSegment(lineSegment_t segment, ComplexNumber point);

void Task1_ReadNumbersFromUser(ComplexNumber arr[5]);

#endif // FUNCTIONS_LIB
