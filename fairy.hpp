#ifndef FAIRY_HPP
#define FAIRY_HPP
#include "creature.hpp"

class Fairy : public Creature {
public:
    Fairy() : Creature("Fairy", 4, 1, 3, Element::Air) {}

    std::unique_ptr<Creature> clone() const override;
    void on_play(Player& owner) override;
};
#endif