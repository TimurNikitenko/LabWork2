#ifndef FAIRY_HPP
#define FAIRY_HPP
#include "creature.hpp"

class Fairy : public Creature {
public:
    Fairy() : Creature("Fairy", 1, 1, 3, Element::Water) {}

    void on_play(Player& owner) override {
        // TODO: Implement mana stealing effect
    }
};
#endif

