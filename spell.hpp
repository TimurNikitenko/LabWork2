#ifndef SPELL_HPP
#define SPELL_HPP
#include "card.hpp"

class Creature; // Forward declaration

// spell.hpp
class Spell : public Card {
    public:
        Spell(std::string name, int cost, std::string desc) 
            : Card(name, cost), description_(std::move(desc)) {}
    
        virtual bool needs_target() const { return false; }
        virtual bool can_target_self() const { return false; }
        virtual bool can_target_creatures() const { return false; }
        
        virtual void play(Player& owner, Player& opponent, void* target = nullptr) override = 0;
        
    protected:
        std::string description_;
    };
#endif