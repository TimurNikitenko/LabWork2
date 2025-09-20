#include "dragon.hpp"
#include "game.hpp"
#include <iostream>

std::unique_ptr<Creature> Dragon::clone() const {
    return std::make_unique<Dragon>(*this);
}

void Dragon::on_death() {
    // Dragon explodes when it dies, dealing 2 damage to the opponent
    Game& game = Game::get();
    
    // Find which player owns this dragon and damage the opponent
    // Check if this dragon is on the human's board
    bool is_human_dragon = false;
    for (const auto& creature : game.human().board()) {
        if (creature.get() == this) {
            is_human_dragon = true;
            break;
        }
    }
    
    if (is_human_dragon) {
        // This is the human's dragon, damage the AI
        game.ai().take_damage(2);
        std::cout << "Dragon explodes! AI takes 2 damage!" << std::endl;
    } else {
        // This is the AI's dragon, damage the human
        game.human().take_damage(2);
        std::cout << "Dragon explodes! Player takes 2 damage!" << std::endl;
    }
}
