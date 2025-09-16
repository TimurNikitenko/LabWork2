#ifndef SHADOW_MAGE_HPP
#define SHADOW_MAGE_HPP
#include "creature.hpp"

class ShadowMage : public Creature {
public:
    ShadowMage() : Creature("Shadow Mage", 5, 3, 3, Element::None) {}
    void on_attack(Creature& target) override;
};
#endif
