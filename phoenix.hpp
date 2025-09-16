#ifndef PHOENIX_HPP
#define PHOENIX_HPP
#include "creature.hpp"

class Phoenix : public Creature {
public:
    Phoenix() : Creature("Phoenix", 6, 4, 3, Element::Fire) {}
    void on_death() override;
private:
    bool has_revived_ = false;
};
#endif
