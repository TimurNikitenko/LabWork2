#include "basilisk.hpp"
#include <iostream>

std::unique_ptr<Creature> Basilisk::clone() const {
    return std::make_unique<Basilisk>(*this);
}

void Basilisk::on_attack(Creature& target) {
    // Basilisk's petrifying gaze exhausts the target creature
    // The target won't be able to attack next turn
    target.petrified_ = true;
    std::cout << "Basilisk's petrifying gaze exhausts " << target.name_ 
              << " - it cannot attack next turn!" << std::endl;
}