#include "ComplexNumber.hpp"
#include "tfunctions.hpp"

#include "task1.cpp"
#include "task2.cpp"
#include "task3.cpp"

#include <cstring>
#include <iostream>

const char* taskMessageBegin = "Task #";
const char* taskMessageEnd = "-----\n";

void printTaskBegin(const ProgramOptions& options, int choice)
{
   const std::string message = taskMessageBegin + std::to_string(choice) + '\n';
   printMessage(options, message.c_str());
}

void printTaskEnd(const ProgramOptions& options)
{
   printMessage(options, taskMessageEnd);
}

int main(int argc, char const* argv[])
{
   int parameters = argc;
   ProgramOptions options;
   bool useStdinToInit = false;
   if (parameters == 1) {
      printMessage(options, "Enter program number to launch: ");
      parameters = 2;
      useStdinToInit = true;
   }
   for (int i = 1; i < parameters; i++) {
      int choice, returnCode = 0;
      if (useStdinToInit) {
         std::cin >> choice;
         std::cin.ignore();
      } else {
         if (strcmp(argv[i], "-d") == 0) {
            options.outputStyle = ProgramOptions::UNIX;
            continue;
         }
         choice = std::stoi(argv[i]);
      }

      switch (choice) {
         case 1:
            printTaskBegin(options, choice);
            task1::solve(returnCode, options);
            printTaskEnd(options);
            break;
         case 5:
            printTaskBegin(options, choice);
            task5::solve(returnCode, options);
            printTaskEnd(options);
            break;
         default:
            std::cerr << "Entered program number is incorrect, retry.\n";
            break;
      }

      if (returnCode != EXIT_SUCCESS)
         return returnCode;
   }
}
