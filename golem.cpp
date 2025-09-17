#include "golem.hpp"

std::unique_ptr<Creature> Golem::clone() const {
    return std::make_unique<Golem>(*this);
}