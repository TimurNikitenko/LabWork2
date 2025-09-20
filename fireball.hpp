#ifndef FIREBALL_HPP
#define FIREBALL_HPP
#include "spell.hpp"
#include "player.hpp"

class Creature; // Forward declaration

// fireball.hpp
class Fireball : public Spell {
    public:
        Fireball() : Spell("Fireball", 3, "Deal 4 damage to target") {}
    
        bool needs_target() const override { return true; }
        bool can_target_creatures() const override { return true; }
    
        void play(Player& owner, Player& opponent, void* target = nullptr) override {
            // Call base class to handle mana deduction
            Spell::play(owner, opponent, target);
            
            Creature* creature_target = static_cast<Creature*>(target);
            if (creature_target) {
                // Deal 4 damage to target creature
                creature_target->take_damage(4);
            } else {
                // Deal 4 damage to opponent if no creature target
                opponent.take_damage(4);
            }
        }
    };
#endif
