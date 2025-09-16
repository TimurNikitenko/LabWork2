#ifndef GRIFFIN_HPP
#define GRIFFIN_HPP
#include "creature.hpp"

class Griffin : public Creature {
public:
    Griffin() : Creature("Griffin", 3, 2, 4, Element::Air) {}
    void modify_health(int amount);
};
#endif
