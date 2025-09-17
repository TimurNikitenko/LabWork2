#include "phoenix.hpp"

std::unique_ptr<Creature> Phoenix::clone() const {
    return std::make_unique<Phoenix>(*this);
}
