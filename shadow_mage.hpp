#ifndef SHADOW_MAGE_HPP
#define SHADOW_MAGE_HPP
#include "creature.hpp"

class ShadowMage : public Creature {
public:
    ShadowMage() : Creature("Shadow Mage", 4, 3, 2, Element::None) {}

    std::unique_ptr<Creature> clone() const override;
};
#endif