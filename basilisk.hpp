#ifndef BASILISK_HPP
#define BASILISK_HPP
#include "creature.hpp"

class Basilisk : public Creature {
public:
    Basilisk() : Creature("Basilisk", 4, 3, 5, Element::Earth) {}
    void on_attack(Creature& target) override;
};
#endif
