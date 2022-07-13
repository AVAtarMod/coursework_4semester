#include "ComplexNumber.hpp"
#include "functions.hpp"

#include "task1.cpp"
#include "task2.cpp"
#include "task3.cpp"

#include <iostream>

int main(int argc, char const* argv[])
{
    bool noData = false;
    if (argc == 1) {
        std::cout << "Enter program number to launch: ";
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++) {
        int choice;
        if (noData) {
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        } else {
            choice = std::stoi(argv[i]);
        }

        switch (choice) {
        case 1:
            std::cout << "Task #1\n";
            task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Task #2\n";
            task2();
            std::cout << "-----\n";
            break;
        case 3:
            std::cout << "Task #3\n";
            task3();
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Entered program number is incorrect, retry.\n";
            break;
        }
    }
}
