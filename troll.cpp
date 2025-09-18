#include "troll.hpp"
#include <iostream>

std::unique_ptr<Creature> Troll::clone() const {
    return std::make_unique<Troll>(*this);
}

void Troll::start_turn() {
    // Call base class to clear petrify
    Creature::start_turn();
    
    // Troll regenerates 1 health each turn (but can't exceed original health)
    if (health_ < 4) {  // Original health is 4
        health_++;
        std::cout << "Troll's regeneration heals 1 health! (Health: " << health_ << ")" << std::endl;
    }
}