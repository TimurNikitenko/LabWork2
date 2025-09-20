// input_handler.hpp
#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <string>
#include <functional>
#include <vector>

class InputHandler {
public:
    struct MenuOption {
        std::string description;
        std::function<void()> action;
        char shortcut;
    };

    void display_menu(const std::vector<MenuOption>& options);
    int get_int_input(const std::string& prompt, int min, int max);
    bool get_confirmation(const std::string& prompt);
    void clear_screen() const;
};

#endif
