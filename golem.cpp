#include "golem.hpp"
#include "player.hpp"
#include <iostream>

std::unique_ptr<Creature> Golem::clone() const {
    return std::make_unique<Golem>(*this);
}

void Golem::on_play(Player& owner) {
    // Golem's sturdy nature permanently increases the player's maximum health
    owner.modify_health(1);
    std::cout << "Golem's sturdy presence permanently increases " << owner.name() 
              << "'s maximum health by 1!" << std::endl;
}