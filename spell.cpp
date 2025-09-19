#include "spell.hpp"
#include "player.hpp"

void Spell::play(Player& owner, Player& opponent, void* target) {
    if (owner.mana() >= cost_) {
        owner.use_mana(cost_);
        // TODO: Implement spell effects
    }
}
