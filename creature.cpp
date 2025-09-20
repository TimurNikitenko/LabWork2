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
    (void)opponent; (void)target;
    auto creature_clone = clone();
    Game::get().spawn_creature(std::move(creature_clone), owner);
}

void Creature::attack(Creature& target) {
    if (!can_attack_ || petrified_) return;

    // Trigger on_attack ability before dealing damage
    on_attack(target);
    
    // Resolve combat (both creatures take damage)
    resolve_combat(target);
    
    can_attack_ = false;
}

void Creature::resolve_combat(Creature& target) {
    // Calculate damage dealt by attacker
    int attackerDamage = attack_ + 
                        ElementUtils::combat_modifier(element_, target.element_);
    
    // Calculate damage dealt by defender
    int defenderDamage = target.attack_ + 
                        ElementUtils::combat_modifier(target.element_, element_);
    
    // Both creatures take damage
    target.take_damage(attackerDamage);
    take_damage(defenderDamage);
}

void Creature::take_damage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
        // Trigger on_death ability before destroying
        on_death();
        Game::get().destroy_creature(this);
    }
}

bool Creature::is_alive() const {
    return health_ > 0;
}
