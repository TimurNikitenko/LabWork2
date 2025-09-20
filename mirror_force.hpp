#ifndef MIRROR_FORCE_HPP
#define MIRROR_FORCE_HPP
#include "trap.hpp"
#include "player.hpp"
#include <iostream>

// mirror_force.hpp
class MirrorForce : public Trap {
    public:
        MirrorForce() : Trap("Mirror Force", 3) {}
    
        bool check_trigger(const Player& triggerer) const {
            // Simple trigger - activate when opponent has 2+ creatures
            return triggerer.board().size() >= 2;
        }
    
        void resolve(Player& owner, Player& triggerer) {
            (void)owner;
            std::cout << "Mirror Force activates!\n";
            // Deal 2 damage to opponent
            triggerer.take_damage(2);
        }
    };
#endif
