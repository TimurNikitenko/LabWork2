#include "shadow_mage.hpp"

std::unique_ptr<Creature> ShadowMage::clone() const {
    return std::make_unique<ShadowMage>(*this);
}