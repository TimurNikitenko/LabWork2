#ifndef BASILISK_HPP
#define BASILISK_HPP
#include "creature.hpp"
#include <iostream>

class Basilisk : public Creature {
public:
    Basilisk() : Creature("Basilisk", 3, 3, 5, Element::Earth) {}

    std::unique_ptr<Creature> clone() const override;
    void on_attack(Creature& target) override;
};
#endif