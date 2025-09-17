#ifndef PHOENIX_HPP
#define PHOENIX_HPP
#include "creature.hpp"

class Phoenix : public Creature {
public:
    Phoenix() : Creature("Phoenix", 6, 4, 3, Element::Fire) {}
    std::unique_ptr<Creature> clone() const override;
};
#endif
