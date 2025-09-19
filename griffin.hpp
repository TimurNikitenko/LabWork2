#ifndef GRIFFIN_HPP
#define GRIFFIN_HPP
#include "creature.hpp"

class Griffin : public Creature {
public:
    Griffin() : Creature("Griffin", 3, 2, 4, Element::Air) {}
    void modify_health(int amount);
    std::unique_ptr<Creature> clone() const override;
    
    // Griffin can attack opponent directly even if enemy creatures are present
    bool can_attack_opponent_directly() const override { return true; }
};
#endif
