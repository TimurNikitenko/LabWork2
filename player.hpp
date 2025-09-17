#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include <memory>
#include <string>
#include "card.hpp"
#include "creature.hpp"
#include "artifact.hpp"

class Deck;
class Creature;
class Trap;
class Artifact;
class Game;

class Player {
public:
    Player(std::string name, int health);

    // ---------- Core Gameplay ----------
    void draw_card(Deck& deck);
    bool play_card(size_t index, Player& opponent);
    void end_turn();
    void remove_card_from_hand(size_t index);
    bool remove_from_board(Creature* creature);
    void add_to_board(std::unique_ptr<Creature> creature);

    // ---------- Combat ----------
    void modify_health(int amount) { 
        health_ = std::max(0, health_ + amount); 
        if (health_ <= 0) {
            // Game will check win conditions
        }
    }
    void heal(int amount);
    void take_damage(int amount);

    // ---------- Mana ----------
    void refresh_mana(int turn_number) { 
        max_mana_ = std::min(turn_number, 10);  // Max mana = turn number, caps at 10
        mana_ = max_mana_;  // Refill mana to max
    }
    void use_mana(int amount);
    void reset_mana();
    void gain_mana(int amount);
    void modify_mana(int amount);
    void increase_max_mana(int amount);

    // ---------- Traps ----------
    void trigger_traps(Player& opponent);
    void resolve_traps(Player& triggerer);
    void remove_trap(Trap* trap);
    void set_trap(Trap* trap);

    // ---------- Accessors ----------
    const auto& board() const { return board_; }
    auto& board() { return board_; }
    const auto& hand() const { return hand_; }
    const auto& traps() const { return traps_; }
    bool alive() const { return health_ > 0; }
    bool can_play(int cost) const { return mana_ >= cost; }
    const std::string& name() const { return name_; }
    int mana() const { return mana_; }
    int max_mana() const { return max_mana_; }
    int health() const { return health_; }
    void print_status() const;

private:
    std::string name_;
    int health_;
    int mana_ = 0;
    int max_mana_ = 0;
    std::vector<std::unique_ptr<Card>> hand_;
    std::vector<std::unique_ptr<Creature>> board_;
    std::vector<std::unique_ptr<Artifact>> artifacts_;
    std::vector<Trap*> traps_;  // Non-owning (owned by hand_)
    void add_artifact(Artifact* artifact) {
        artifacts_.push_back(std::unique_ptr<Artifact>(artifact));
    }

    const auto& artifacts() const { return artifacts_; }

    // Trap management
};
#endif
