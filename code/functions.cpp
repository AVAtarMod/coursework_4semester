#include "functions.hpp"

void Task1_ReadNumbersFromUser(ComplexNumber arr[5])
{
    const size_t labelsCount = 5;
    std::string labels[labelsCount] { "a", "b", "c", "a1", "b1" };

    bool isTriangle = false, isValidA1 = false, isValidB1 = false;
    while (!(isTriangle && isValidA1 && isValidB1)) {
        std::cout << "Введите координаты точек a,b,c,a1,b1:\n";
        for (size_t i = 0; i < labelsCount; i++) {
            std::cout << "  " << labels[i] << ": ";
            std::cin >> numbers[i];
        }
        isTriangle = a * (b - c) + b * (c - a) + c * (a - b)
            == ComplexNumber::getZero();
        isValidA1 = ComplexNumber::isOnSameLine(b, c, a1) && (a1.Im < std::max(b.Im, c.Im)) && (a1.Re < std::max(b.Re, c.Re));
        isValidB1 = ComplexNumber::isOnSameLine(a, c, b1) && (b1.Im < std::max(a.Im, c.Im)) && (b1.Re < std::max(a.Re, c.Re));
        if (!isTriangle)
            std::cout << "Некорректные a,b,c. Должны быть точками треугольника ABC\n";
        if (!isValidA1)
            std::cout << "Некорректная a1. Должна быть на отрезке BC\n";
        if (!isValidB1)
            std::cout << "Некорректная b1. Должна быть на отрезке AC\n";
    }
}
