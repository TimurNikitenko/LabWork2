#include "dragon.hpp"

std::unique_ptr<Creature> Dragon::clone() const {
    return std::make_unique<Dragon>(*this);
}
