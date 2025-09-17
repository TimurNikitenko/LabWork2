#include "wizard.hpp"

std::unique_ptr<Creature> Wizard::clone() const {
    return std::make_unique<Wizard>(*this);
}