#ifndef SIREN_HPP
#define SIREN_HPP
#include "creature.hpp"

class Siren : public Creature {
public:
    Siren() : Creature("Siren", 4, 2, 5, Element::Water) {}
    void on_play(Player& owner) override {
        // TODO: Implement enemy weakening effect
    }
};
#endif
