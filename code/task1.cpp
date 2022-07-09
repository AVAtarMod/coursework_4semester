#include "ComplexNumber.hpp"
#include "functions.hpp"

inline void task1()
{
    const int numbersCount = 9;
    ComplexNumber numbers[numbersCount];
    // Reference for readability
    ComplexNumber &a = numbers[0],
                  &b = numbers[1],
                  &c = numbers[2],
                  &a1 = numbers[3],
                  &b1 = numbers[4],
                  &c1 = numbers[5],
                  &m = numbers[6],
                  &n = numbers[7],
                  &p = numbers[8];

    Task1_ReadNumbersFromUser(numbers);

    std::pair<ComplexNumber, ComplexNumber> pairs[2] { { a, b }, { b1, a1 } };

    c1 = intersect(pairs[0], pairs[1]);
    m = ComplexNumber::middle(a, a1);
    n = ComplexNumber::middle(b, b1);
    p = ComplexNumber::middle(c, c1);

    if (ComplexNumber::isOnSameLine(m, n, p)) {
        for (size_t i = 0; i < numbersCount; i++) {
            std::cout << numbers[i] << "\n";
        }
    }
}
