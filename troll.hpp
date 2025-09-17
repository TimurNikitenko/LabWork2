#ifndef TROLL_HPP
#define TROLL_HPP
#include "creature.hpp"

class Troll : public Creature {
public:
    Troll() : Creature("Troll", 2, 2, 4, Element::Earth) {}

    std::unique_ptr<Creature> clone() const override;
};
#endif