#include "ComplexNumber.hpp"
#include "functions.hpp"

void task5::solve(int& returnCode)
{
    returnCode = 0;
    // TODO test on cw-main data (or almost same data)
    const int numbersCount = 9;
    ComplexNumber numbers[numbersCount];
    const std::string labels[numbersCount] = { "A", "B", "C", "A1", "B1", "C1", "M", "N", "P" };
    // References for readability
    ComplexNumber &a = numbers[0],
                  &b = numbers[1],
                  &c = numbers[2],
                  &a1 = numbers[3],
                  &b1 = numbers[4],
                  &c1 = numbers[5],
                  &m = numbers[6],
                  &n = numbers[7],
                  &p = numbers[8];

    readNumbersFromUser(numbers, labels, returnCode);
    if (returnCode != EXIT_SUCCESS)
        return;

    std::pair<ComplexNumber, ComplexNumber> pairs[2] { { a, b }, { b1, a1 } };

    c1 = intersect(pairs[0], pairs[1]);
    m = ComplexNumber::middle(a, a1);
    n = ComplexNumber::middle(b, b1);
    p = ComplexNumber::middle(c, c1);

    if (ComplexNumber::isOnSameLine(m, n, p)) {
        // TODO use special function here
        std::cout << "Computed coordinates:\n";
        for (size_t i = 0; i < numbersCount; i++) {
            std::cout << " " + labels[i] + ": " << numbers[i] << "\n";
        }
    } else
        std::cerr << "The computed points M,N,P is not belong to the same line, so the Guss's theorem is not true.\n";
}
