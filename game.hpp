// game.hpp
#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "player.hpp"
#include "deck.hpp"
#include "creature.hpp"
#include "input_handler.hpp"

class Spell;  // Forward declaration

class Game {
private:
    static Game* instance_;
    InputHandler input_handler_;
    Player human_;
    Player ai_;
    Deck deck_;
    int turn_count_;
    bool game_over_;

    // Private constructor
    Game() : human_("Player", 20), ai_("AI", 20), turn_count_(0), game_over_(false) {}

public:
    // Singleton access
    static Game& get() {
        if (!instance_) instance_ = new Game();
        return *instance_;
    }
    
    // Reset singleton instance (for testing)
    static void reset_instance();

    // Core Game Loop
    void human_play_phase();
    void start_game();
    void process_turn();
    void end_turn();
    bool is_over() const { return game_over_; }

    // Phase Handlers
    void draw_phase(Player& player);
    void play_phase(Player& player);
    void attack_phase(Player& player);

    // Combat
    void attack(Creature& attacker, Creature& target);
    void attack_player(Creature& attacker, Player& target);
    
    // Creature Management
    Creature* spawn_creature(std::unique_ptr<Creature> creature, Player& owner);
    void destroy_creature(Creature* creature);
    Creature* find_weakest_enemy(const Player& opponent) const;

    // Win Conditions
    bool check_win_conditions();
    void resolve_tie();
    
    // Player access methods
    Player& human() { return human_; }
    Player& ai() { return ai_; }
    const Player& human() const { return human_; }
    const Player& ai() const { return ai_; }
    
    // Testing methods
    int get_ai_health() const { return ai_.health(); }
    void reduce_ai_health(int amount) { ai_.modify_health(-amount); }

    // UI Methods
    void display_boards() const;
    void display_hand() const;
    void display_game_state() const;
    void play_card_menu();
    void ai_take_turn();
    bool validate_target(const Spell& spell, Player& target, Creature* creature);

    // Cleanup
    ~Game() { 
        delete instance_; 
        instance_ = nullptr;
    }

    // Delete copy/move
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
#endif
