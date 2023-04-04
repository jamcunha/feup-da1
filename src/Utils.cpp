#include "Utils.h"

#include <iostream>

void utils::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Computing...\n"; // in case the screen is not cleared fast enough
    std::cout << "\033[2J\033[1;1H";
}

void utils::waitEnter() {
    std::cout << "\nPress <Enter> to continue...";

    while(std::cin.get() != '\n');

    utils::clearScreen();
}
