#include "wizard.hpp"
#include "player.hpp"
#include <iostream>

std::unique_ptr<Creature> Wizard::clone() const {
    return std::make_unique<Wizard>(*this);
}

void Wizard::on_play(Player& owner) {
    // Wizard's magical knowledge increases the player's mana capacity
    owner.increase_max_mana(1);
    std::cout << "Wizard's magical knowledge increases " << owner.name() 
              << "'s maximum mana by 1!" << std::endl;
}