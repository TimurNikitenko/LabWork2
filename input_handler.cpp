// input_handler.cpp
#include "input_handler.hpp"
#include <iostream>
#include <limits>
#include <cctype>

void InputHandler::display_menu(const std::vector<MenuOption>& options) {
    std::cout << "\n=== Available Actions ===\n";
    for (const auto& option : options) {
        std::cout << "[" << option.shortcut << "] " << option.description << "\n";
    }
    std::cout << std::endl;
}

int InputHandler::get_int_input(const std::string& prompt, int min, int max) {
    int choice;
    while (true) {
        std::cout << prompt << " [" << min << "-" << max << "]: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice >= min && choice <= max) break;
        std::cout << "Input out of range. Try again.\n";
    }
    return choice;
}

bool InputHandler::get_confirmation(const std::string& prompt) {
    char response;
    std::cout << prompt << " [y/n]: ";
    std::cin >> response;
    return std::tolower(response) == 'y';
}

void InputHandler::clear_screen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
