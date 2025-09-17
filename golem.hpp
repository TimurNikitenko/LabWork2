#ifndef GOLEM_HPP
#define GOLEM_HPP
#include "creature.hpp"

class Golem : public Creature {
public:
    Golem() : Creature("Golem", 3, 2, 8, Element::Earth) {}

    void take_damage(int amount) {
        health_ -= std::max(1, amount - 1); // Always takes at least 1 less
    }
    std::unique_ptr<Creature> clone() const override;
};
#endif
