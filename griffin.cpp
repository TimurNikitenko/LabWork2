#include "griffin.hpp"

std::unique_ptr<Creature> Griffin::clone() const {
    return std::make_unique<Griffin>(*this);
}