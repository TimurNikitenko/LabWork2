#ifndef LIGHTNING_BOLT_HPP
#define LIGHTNING_BOLT_HPP
#include "spell.hpp"
#include "player.hpp"

class LightningBolt : public Spell {
public:
    LightningBolt() : Spell("Lightning Bolt", 4, "Deal 3 damage, 5 if opponent has Air creatures") {}
    
    void play(Player& owner, Player& opponent, void* target = nullptr) override {
        // Call base class to handle mana deduction
        Spell::play(owner, opponent, target);
        
        int damage = 3;
        for (const auto& creature : opponent.board()) {
            if (creature->element_ == Element::Air) {
                damage = 5;
                break;
            }
        }
        opponent.take_damage(damage);
    }
};
#endif
