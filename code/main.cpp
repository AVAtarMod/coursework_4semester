#include "ComplexNumber.hpp"
#include "functions.hpp"

#include "task1.cpp"
#include "task2.cpp"
#include "task3.cpp"

#include <iostream>

int main(int argc, char const* argv[])
{
    int parameters = argc;
    bool useStdinToInit = false;
    if (parameters == 1) {
        std::cout << "Enter program number to launch: ";
        parameters = 2;
        useStdinToInit = true;
    }
    for (int i = 1; i < parameters; i++) {
        int choice, returnCode = 0;
        if (useStdinToInit) {
            std::cin >> choice;
            std::cin.ignore();
        } else {
            choice = std::stoi(argv[i]);
        }

        switch (choice) {
        case 2:
            std::cout << "Task #2\n";
            // task2();
            std::cout << "-----\n";
            break;
        case 3:
            std::cout << "Task #3\n";
            // task3();
            std::cout << "-----\n";
            break;
        case 5:
            std::cout << "Task #5\n";
            task5::solve(returnCode);
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Entered program number is incorrect, retry.\n";
            break;
        }

        if (returnCode != EXIT_SUCCESS)
            return returnCode;
    }
}
