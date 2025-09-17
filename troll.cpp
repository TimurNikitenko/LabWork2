#include "troll.hpp"

std::unique_ptr<Creature> Troll::clone() const {
    return std::make_unique<Troll>(*this);
}