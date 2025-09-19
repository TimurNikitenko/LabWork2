#include "fairy.hpp"
#include "game.hpp"
#include "player.hpp"
#include <iostream>

std::unique_ptr<Creature> Fairy::clone() const {
    return std::make_unique<Fairy>(*this);
}

void Fairy::on_play(Player& owner) {
    // Get the opponent player
    Game& game = Game::get();
    Player& opponent = (&owner == &game.human()) ? game.ai() : game.human();
    
    // Steal 2 max mana from opponent (permanent effect) - more visible impact
    if (opponent.max_mana() >= 2) {
        opponent.increase_max_mana(-2);  // Reduce opponent's max mana by 2
        owner.increase_max_mana(2);      // Increase owner's max mana by 2
        std::cout << "Fairy's powerful magical theft permanently steals 2 max mana from " 
                  << opponent.name() << " and gives it to " << owner.name() << "!" << std::endl;
    } else if (opponent.max_mana() >= 1) {
        // If opponent only has 1 mana, steal that 1 mana
        opponent.increase_max_mana(-1);
        owner.increase_max_mana(1);
        std::cout << "Fairy's magical theft permanently steals 1 max mana from " 
                  << opponent.name() << " and gives it to " << owner.name() << "!" << std::endl;
    } else {
        std::cout << "Fairy tries to steal mana from " << opponent.name() 
                  << " but they have no max mana to steal!" << std::endl;
    }
}
