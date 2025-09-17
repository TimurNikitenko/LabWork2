#include "fairy.hpp"

std::unique_ptr<Creature> Fairy::clone() const {
    return std::make_unique<Fairy>(*this);
}
