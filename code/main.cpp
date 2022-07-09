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
        std::cout << "Введите программу для запуска: ";
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
            std::cout << "Задача №1\n";
            task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Задача №2\n";
            task2();
            std::cout << "-----\n";
            break;
        case 3:
            std::cout << "Задача №3\n";
            task3();
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Номер задачи введён не верно либо не удалось конвертировать введённые данные\n";
            break;
        }
    }
}
