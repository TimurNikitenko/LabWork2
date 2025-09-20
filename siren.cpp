#include "siren.hpp"

std::unique_ptr<Creature> Siren::clone() const {
    return std::make_unique<Siren>(*this);
}