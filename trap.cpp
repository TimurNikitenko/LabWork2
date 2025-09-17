#include "trap.hpp"
#include "player.hpp"

Trap::Trap(std::string name, int cost) : Card(name, cost) {
    is_face_down = true; // Traps are always face-down when played
}

void Trap::play(Player& owner, Player& opponent, void* target) {
    if (owner.mana() >= cost_) {
        owner.use_mana(cost_);
        owner.set_trap(this); // Register with player
    }
}

bool Trap::check_trigger(const Player& triggerer) const {
    // TODO: Implement trap trigger logic
    return false;
}

void Trap::resolve(Player& owner, Player& triggerer) {
    // TODO: Implement trap resolution logic
}
