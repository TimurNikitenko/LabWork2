#include "creature.hpp"
#include "player.hpp"
#include "game.hpp"
#include "element_utils.hpp"

Creature::Creature(std::string name, int cost, int attack, int health, Element element) 
    : Card(name, cost), 
      attack_(attack), 
      health_(health), 
      element_(element),
      can_attack_(false) {}  // Can't attack the turn it's played

void Creature::play(Player& owner, Player& opponent, void* target) {
    // Spawn this creature on the owner's board
    Game::get().spawn_creature(*this, owner);
}

void Creature::attack(Creature& target) {
    if (!can_attack_) return;

    int damage = attack_ + 
                 ElementUtils::combat_modifier(element_, target.element_);
    
    target.take_damage(damage);
    can_attack_ = false;
}

void Creature::take_damage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
        Game::get().destroy_creature(this);
    }
}

bool Creature::is_alive() const {
    return health_ > 0;
}
