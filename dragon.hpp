#ifndef DRAGON_HPP
#define DRAGON_HPP
#include "creature.hpp"

class Dragon : public Creature {
public:
    Dragon() : Creature("Dragon", 4, 5, 4, Element::Fire) {}

    std::unique_ptr<Creature> clone() const override;
};
#endif
