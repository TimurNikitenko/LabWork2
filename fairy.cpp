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
    
    // Steal 1 current mana from opponent (temporary but immediate impact)
    int stolen_mana = std::min(1, opponent.mana());
    if (stolen_mana > 0) {
        opponent.modify_mana(-stolen_mana);
        owner.modify_mana(stolen_mana);
        std::cout << "Fairy steals " << stolen_mana << " mana from " << opponent.name() << "!" << std::endl;
    } else {
        std::cout << "Fairy tries to steal mana from " << opponent.name() << " but they have no mana to steal!" << std::endl;
    }
}
