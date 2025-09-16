#ifndef TROLL_HPP
#define TROLL_HPP
#include "creature.hpp"

class Troll : public Creature {
public:
    Troll() : Creature("Troll", 3, 2, 6, Element::Earth) {}
    
    void on_play(Player& owner) override {
        // TODO: Implement can't attack immediately effect
    }
    
    void end_turn() {
        // TODO: Implement end turn effect
    }
};
#endif
