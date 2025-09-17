#ifndef WIZARD_HPP
#define WIZARD_HPP
#include "creature.hpp"

class Wizard : public Creature {
public:
    Wizard() : Creature("Wizard", 3, 1, 3, Element::None) {}

    std::unique_ptr<Creature> clone() const override;
};
#endif