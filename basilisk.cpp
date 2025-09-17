#include "basilisk.hpp"
#include <iostream>

std::unique_ptr<Creature> Basilisk::clone() const {
    return std::make_unique<Basilisk>(*this);
}