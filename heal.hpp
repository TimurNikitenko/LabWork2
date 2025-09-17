#ifndef HEAL_HPP
#define HEAL_HPP
#include "spell.hpp"
#include "creature.hpp"
#include "player.hpp"
// heal.hpp
class Heal : public Spell {
    public:
        Heal() : Spell("Heal", 2, "Restore 5 health to target") {}
    
        bool needs_target() const override { return false; }  // Heal always targets self
        bool can_target_self() const override { return true; }
    
        void play(Player& owner, Player& opponent, void* target = nullptr) override {
            // Call base class to handle mana deduction
            Spell::play(owner, opponent, target);
            
            // Heal the owner (self-targeting)
            owner.heal(5);
        }
    };
#endif
