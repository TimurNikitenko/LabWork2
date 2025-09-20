#ifndef MANA_SURGE_HPP
#define MANA_SURGE_HPP
#include "spell.hpp"
#include "player.hpp"

class ManaSurge : public Spell {
public:
    ManaSurge() : Spell("Mana Surge", 1, "Increase max mana by 2") {}
    
    void play(Player& owner, Player& opponent, void* target = nullptr) override {
        // Call base class to handle mana deduction
        Spell::play(owner, opponent, target);
        
        // TODO: Implement mana cap increase
        // For now, just give immediate mana
        owner.gain_mana(2);
    }
};
#endif
