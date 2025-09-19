#ifndef SIREN_HPP
#define SIREN_HPP
#include "creature.hpp"

class Siren : public Creature {
public:
    Siren() : Creature("Siren", 3, 2, 4, Element::Water) {}

    std::unique_ptr<Creature> clone() const override;
};
#endif