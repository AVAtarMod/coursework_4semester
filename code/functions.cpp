#include "functions.hpp"
#include "Line.hpp"

#include <cmath>

ComplexNumber intersect(lineSegment_t first, lineSegment_t second)
{
    Line firstL(first.first, first.second), secondL(second.first, second.second);

    double x = (secondL.B() - firstL.B()) / (firstL.K() - secondL.K());
    double tmp = firstL.y(x);
    double y = std::isinf(tmp) ? secondL.y(x) : tmp;

    return ComplexNumber(x, y);
}

bool isPointBelongsSegment(lineSegment_t segment, ComplexNumber point)
{
    ComplexNumber &a = segment.first, &b = segment.second;
    Line line(a, b);

    double imMax = std::max(a.Im(), b.Im()), imMin = std::min(a.Im(), b.Im());
    double reMax = std::max(a.Re(), b.Re()), reMin = std::min(a.Re(), b.Re());
    bool isPointInBounds
        = (imMin <= point.Im() && point.Im() <= imMax)
        && (reMin <= point.Re() && point.Re() <= reMax);

    return line.isBelongs(point) && isPointInBounds;
}

void Task1_ReadNumbersFromUser(ComplexNumber arr[5], const std::string labels[5])
{
    const size_t labelsCount = 5;

    ComplexNumber &a = arr[0],
                  &b = arr[1],
                  &c = arr[2],
                  &a1 = arr[3],
                  &b1 = arr[4];

    bool isTriangle = false, isValidA1 = false, isValidB1 = false;
    while (!(isTriangle && isValidA1 && isValidB1)) {
        std::cout << "Введите координаты точек a,b,c,a1,b1:\n";
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
        isTriangle = a * (b - c) + b * (c - a) + c * (a - b)
            == ComplexNumber::getZero();

        isValidA1 = isPointBelongsSegment({ b, c }, a1);
        isValidB1 = isPointBelongsSegment({ a, c }, b1);

        if (!isTriangle)
            std::cerr << "Некорректные a,b,c. Должны быть точками треугольника ABC\n";
        if (!isValidA1)
            std::cerr << "Некорректная a1. Должна быть на отрезке BC\n";
        if (!isValidB1)
            std::cerr << "Некорректная b1. Должна быть на отрезке AC\n";
    }
}
