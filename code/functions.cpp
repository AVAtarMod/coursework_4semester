#include "functions.hpp"
#include "Line.hpp"

#include <cmath>

ComplexNumber intersect(clineSegment_t first, clineSegment_t second)
{
    Line firstL(first.first, first.second), secondL(second.first, second.second);

    double x = (secondL.B() - firstL.B()) / (firstL.K() - secondL.K());
    double tmp = firstL.y(x);
    double y = std::isinf(tmp) ? secondL.y(x) : tmp;

    return ComplexNumber(x, y);
}

bool isPointBelongsSegment(clineSegment_t segment, ComplexNumber cpoint)
{
    ComplexNumber &a = segment.first, &b = segment.second;
    Line line(a, b);

    double imMax = std::max(a.Im(), b.Im()), imMin = std::min(a.Im(), b.Im());
    double reMax = std::max(a.Re(), b.Re()), reMin = std::min(a.Re(), b.Re());
    bool isPointInBounds
        = (imMin <= cpoint.Im() && cpoint.Im() <= imMax)
        && (reMin <= cpoint.Re() && cpoint.Re() <= reMax);

    return line.isBelongs(static_cast<Point>(cpoint)) && isPointInBounds;
}

void task1::readTriangleFromUser(ComplexNumber arr[3], const std::string labels[3], int& returnCode)
{
    const size_t labelsCount = 3;

    ComplexNumber &a = arr[0],
                  &b = arr[1],
                  &c = arr[2];

    bool isTriangle = false;
    while (!isTriangle) {
        std::cout << "Enter coordinates of a,b,c,a1,b1 points:\n";
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cout << "User input was canceled. Aborting...\n";
                return;
            }
            std::cin.ignore();
            std::cin.clear();
        }

        for (size_t i = 0; i < labelsCount; i++) {
            std::cout << "  " << labels[i] << ": ";
            std::cin >> arr[i];
        }

        isTriangle = !ComplexNumber::isOnSameLine(a, b, c);
        if (!isTriangle)
            std::cerr << "Incorrect a,b,c. Must be points of the triangle ABC\n";
    }
}

void task5::readNumbersFromUser(ComplexNumber arr[5], const std::string labels[5], int& returnCode)
{
    returnCode = 0;
    const size_t labelsCount = 5;

    ComplexNumber &a = arr[0],
                  &b = arr[1],
                  &c = arr[2],
                  &a1 = arr[3],
                  &b1 = arr[4];

    bool isTriangle = false, isValidA1 = false, isValidB1 = false;
    while (!(isTriangle && isValidA1 && isValidB1)) {
        std::cout << "Enter coordinates of a,b,c,a1,b1 points:\n";
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cerr << "User input was canceled. Aborting...\n";
                returnCode = 1;
                return;
            }
            std::cin.ignore();
            std::cin.clear();
        }
        for (size_t i = 0; i < labelsCount; i++) {
            std::cout << "  " << labels[i] << ": ";
            std::cin >> arr[i];
        }

        isTriangle = !ComplexNumber::isOnSameLine(a, b, c);
        isValidA1 = isPointBelongsSegment({ b, c }, a1);
        isValidB1 = isPointBelongsSegment({ a, c }, b1);

        if (!isTriangle)
            std::cerr << "Incorrect a,b,c. Must be points of the triangle ABC\n";
        if (!isValidA1)
            std::cerr << "The a1 is incorrect. Must belong to segment of line BC\n";
        if (!isValidB1)
            std::cerr << "The b1 is incorrect. Must belong to segment of line AC\n";
    }
}
