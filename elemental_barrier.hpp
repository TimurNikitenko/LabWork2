#ifndef ELEMENTAL_BARRIER_HPP
#define ELEMENTAL_BARRIER_HPP
#include "trap.hpp"
#include "element.hpp"
#include "player.hpp"
#include <iostream>

class ElementalBarrier : public Trap {
private:
    Element blocked_element_;
    
public:
    ElementalBarrier(Element blocked_element) : Trap("Elemental Barrier", 2), blocked_element_(blocked_element) {}
    
    bool check_trigger(const Player& triggerer) const {
        // Trigger if opponent has creatures of the blocked element
        for (const auto& creature : triggerer.board()) {
            if (creature->element_ == blocked_element_) {
                return true;
            }
        }
        return false;
    }
    
    void resolve(Player& owner, Player& triggerer) {
        (void)owner;
        std::cout << "Elemental Barrier activates!\n";
        // Deal 2 damage to opponent
        triggerer.take_damage(2);
    }
};
#endif
