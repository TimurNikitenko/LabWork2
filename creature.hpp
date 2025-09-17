#ifndef CREATURE_HPP
#define CREATURE_HPP
#include "card.hpp"
#include "element.hpp"
#include <memory>

class Creature : public Card {
public:
    Creature(std::string name, int cost, int attack, int health, Element element);
    virtual ~Creature() = default;

    // Core methods (no getters, direct access)
    void play(Player& owner, Player& opponent, void* target = nullptr) override;
    void attack(Creature& target);
    void resolve_combat(Creature& target);
    void modify_health(int amount) { health_ += amount; }
    bool alive() const { return health_ > 0; }
    bool is_alive() const;
    void take_damage(int amount);
    void ready() { can_attack_ = true; }
    void end_turn() { can_attack_ = true; }

    // Events (override in derived classes)
    virtual void on_play(Player& owner) {}
    virtual void on_attack(Creature& target) {}
    virtual void on_death() {}
    
    // Clone method for polymorphic copying
    virtual std::unique_ptr<Creature> clone() const = 0;

    // Public fields for combat (simplified access)
    Element element_;
    int attack_;
    int health_;
    bool can_attack_ = false;
};
#endif
