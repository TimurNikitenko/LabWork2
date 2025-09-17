// game.cpp
#include "game.hpp"
#include "element_utils.hpp"
#include "spell.hpp"
#include "trap.hpp"
#include <iostream>
#include <limits>

// Static member definition
Game* Game::instance_ = nullptr;

void Game::start_game() {
    deck_.shuffle();
    
    // Draw starting hands
    for (int i = 0; i < 5; ++i) {
        human_.draw_card(deck_);
        ai_.draw_card(deck_);
    }
}

void Game::process_turn() {
    // Check if game is already over
    if (game_over_) {
        return;
    }
    
    Player& active_player = (turn_count_ % 2 == 0) ? human_ : ai_;
    
    if (!active_player.alive()) {
        game_over_ = true;
        return;
    }

    // Refresh mana at start of turn (both players should have same mana)
    int current_turn = (turn_count_ / 2) + 1;  // Turn 1, 2, 3, etc.
    active_player.refresh_mana(current_turn);
    
    std::cout << "\n=== " << active_player.name() << "'s Turn ===" << std::endl;
    std::cout << "Mana: " << active_player.mana() << "/" << active_player.max_mana() << std::endl;
    
    // 1. Draw Phase
    draw_phase(active_player);
    
    // 2. Play Phase
    play_phase(active_player);
    
    // 3. Attack Phase
    attack_phase(active_player);
    
    // Check for win conditions
    if (check_win_conditions()) {
        game_over_ = true;
        return;
    }
    
    end_turn();
}

void Game::draw_phase(Player& player) {
    if (!deck_.empty()) {
        player.draw_card(deck_);
        std::cout << player.name() << " drew a card" << std::endl;
    }
}


void Game::attack_phase(Player& player) {
    Player& opponent = (&player == &human_) ? ai_ : human_;
    
    // Collect attacks first to avoid modifying board during iteration
    std::vector<std::pair<Creature*, Creature*>> creature_attacks;
    std::vector<std::pair<Creature*, Player*>> player_attacks;
    
    for (auto& creature : player.board()) {
        if (creature->can_attack_) {
            // Check for traps
            
            if (!opponent.board().empty()) {
                Creature* target = find_weakest_enemy(opponent);
                if (target) {
                    creature_attacks.push_back({creature.get(), target});
                }
            } else {
                player_attacks.push_back({creature.get(), &opponent});
            }
        }
    }
    
    
    // Check if any attacks were planned
    if (creature_attacks.empty() && player_attacks.empty()) {
        if (player.board().empty()) {
            std::cout << "No creatures on the board to attack with." << std::endl;
        } else {
            std::cout << "All creatures are exhausted and cannot attack this turn." << std::endl;
        }
        return;
    }
    
    // Show attack phase message
    std::cout << "\n=== Attack Phase ===" << std::endl;
    
    // Execute creature attacks (using index-based loop to avoid iterator invalidation)
    for (size_t i = 0; i < creature_attacks.size(); ++i) {
        
        if (game_over_) {
            break; 
        }
        
        auto& attack_pair = creature_attacks[i];
        
        // Check if both creatures are still alive before attacking
        if (!attack_pair.first || !attack_pair.second) {
            continue;
        }
        
        // Check if creatures are still on the board (safer than checking is_alive on potentially freed memory)
        bool attacker_found = false;
        bool defender_found = false;
        
        // Check if attacker is still on human's board
        for (const auto& creature : human_.board()) {
            if (creature.get() == attack_pair.first) {
                attacker_found = true;
                break;
            }
        }
        
        // Check if defender is still on AI's board
        for (const auto& creature : ai_.board()) {
            if (creature.get() == attack_pair.second) {
                defender_found = true;
                break;
            }
        }
        
        if (!attacker_found || !defender_found) {
            continue;
        }
        
       
        std::string attacker_name = attack_pair.first->name_;
        std::string defender_name = attack_pair.second->name_;
        
        if (!attack_pair.first->is_alive()) {
            continue;
        }
        
        if (!attack_pair.second->is_alive()) {
            continue;
        }
        
        std::cout << attacker_name << " attacks " << defender_name << std::endl;
        attack(*attack_pair.first, *attack_pair.second);
    }
    
   
    for (size_t i = 0; i < player_attacks.size(); ++i) {
        // Check if game is over before each attack
        if (game_over_) {
            break; 
        }
        
        auto& attack_pair = player_attacks[i];
        std::cout << attack_pair.first->name_ << " attacks opponent directly!" << std::endl;
        attack_player(*attack_pair.first, *attack_pair.second);
    }
}

void Game::end_turn() {

    for (size_t i = 0; i < human_.board().size(); ++i) {
        if (human_.board()[i]) {
            human_.board()[i]->end_turn();
        }
    }
    for (size_t i = 0; i < ai_.board().size(); ++i) {
        if (ai_.board()[i]) {
            ai_.board()[i]->end_turn();
        }
    }
    turn_count_++;
}

Creature* Game::find_weakest_enemy(const Player& opponent) const {
    const auto& board = opponent.board();
    if (board.empty()) return nullptr;
    
    return std::min_element(board.begin(), board.end(),
        [](const auto& a, const auto& b) {
            return a->health_ < b->health_;
        })->get();
}

void Game::attack(Creature& attacker, Creature& target) {
    int damage = attacker.attack_ + 
        ElementUtils::combat_modifier(attacker.element_, target.element_);
    

    std::string attacker_name = attacker.name_;
    std::string target_name = target.name_;
    
    std::cout << attacker_name << " deals " << damage << " damage to " 
              << target_name << std::endl;
    
    // Trigger on_attack ability before dealing damage
    attacker.on_attack(target);
    
    target.take_damage(damage);
    attacker.can_attack_ = false; 
   
}

void Game::attack_player(Creature& attacker, Player& target) {
    target.modify_health(-attacker.attack_);
    attacker.can_attack_ = false; 
    std::cout << attacker.name_ << " deals " << attacker.attack_ 
              << " damage to opponent" << std::endl;
    
    // Check win conditions immediately after dealing damage
    if (check_win_conditions()) {
        return;
    }
}

Creature* Game::spawn_creature(std::unique_ptr<Creature> creature, Player& owner) {
    if (owner.board().size() >= 5) {
        std::cerr << "Cannot summon more creatures - board full!" << std::endl;
        return nullptr;
    }
    
    Creature* ptr = creature.get();
    ptr->can_attack_ = false; // Newly summoned creatures can't attack this turn
    owner.add_to_board(std::move(creature));
    ptr->on_play(owner);
    
    std::cout << owner.name() << " summoned " << ptr->name_ << std::endl;
    return ptr;
}


void Game::destroy_creature(Creature* creature) {
    if (!creature) return;
    
    std::string creature_name = creature->name_; // Store name before destruction
    std::cout << creature_name << " died!" << std::endl;
    // Note: on_death() is already called in creature.cpp before destroy_creature() is called
    
    // Remove from owner's board (this will destroy the creature)
    // Check both players to find which one owns this creature
    bool removed = false;
    if (human_.remove_from_board(creature)) {
        removed = true;
    } else if (ai_.remove_from_board(creature)) {
        removed = true;
    }
    
    if (!removed) {
        std::cerr << "Warning: Could not find creature " << creature_name << " on any player's board" << std::endl;
    }
}

bool Game::check_win_conditions() {
    if (human_.health() <= 0 && !game_over_) {
        std::cout << "\n=== AI Wins! ===" << std::endl;
        game_over_ = true;
        return true;
    }
    if (ai_.health() <= 0 && !game_over_) {
        std::cout << "\n=== You Win! ===" << std::endl;
        game_over_ = true;
        return true;
    }
    if (deck_.empty() && human_.hand().empty() && ai_.hand().empty()) {
        resolve_tie();
        game_over_ = true;
        return true;
    }
    return false;
}

void Game::resolve_tie() {
    std::cout << "\n=== Game Ended in Tie! ===" << std::endl;
    
    // 1. Compare health
    if (human_.health() != ai_.health()) {
        std::cout << (human_.health() > ai_.health() ? "Human" : "AI") 
                  << " wins by health!" << std::endl;
        return;
    }
    
    // 2. Compare creatures
    if (human_.board().size() != ai_.board().size()) {
        std::cout << (human_.board().size() > ai_.board().size() ? "Human" : "AI") 
                  << " wins by creatures!" << std::endl;
        return;
    }
    
    // 3. Compare mana
    std::cout << (human_.mana() > ai_.mana() ? "Human" : "AI") 
              << " wins by mana!" << std::endl;
}

// Add to game.cpp
void Game::play_phase(Player& player) {
    if (&player == &human_) {
        human_play_phase();
    } else {
        ai_take_turn();
    }
}

void Game::human_play_phase() {
    bool turn_ended = false;
    
    while (!turn_ended && human_.alive() && !game_over_) {
        std::vector<InputHandler::MenuOption> options = {
            {"Play a card", [this]() { play_card_menu(); }, 'p'},
            {"Attack with creatures", [this]() { attack_phase(human_); }, 'a'},
            {"End turn", [this, &turn_ended]() { turn_ended = true; }, 'e'},
            {"View game state", [this]() { display_game_state(); }, 'v'}
        };

        input_handler_.display_menu(options);
        char choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        choice = std::tolower(choice);

        bool valid = false;
        for (const auto& option : options) {
            if (option.shortcut == choice) {
                option.action();
                valid = true;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid choice! Please try again.\n";
        }
        
        // Check if game is over after each action
        if (game_over_) {
            break;
        }
    }
}

void Game::play_card_menu() {
    if (human_.hand().empty()) {
        std::cout << "No cards in hand!\n";
        return;
    }

    display_hand();
    int choice = input_handler_.get_int_input(
        "Select card to play", 
        0, 
        static_cast<int>(human_.hand().size()) - 1
    );

    auto& card = human_.hand()[choice];
    if (human_.mana() < card->cost_) {
        std::cout << "Not enough mana!\n";
        return;
    }

    // Handle all card types
    if (auto* creature = dynamic_cast<Creature*>(card.get())) {
        // Creature card logic
        if (human_.board().size() >= 5) {
            std::cout << "Board is full (max 5 creatures)!\n";
            return;
        }
        // Clone the creature to preserve polymorphic behavior
        auto creature_clone = creature->clone();
        if (spawn_creature(std::move(creature_clone), human_)) {
            std::string creature_name = creature->name_; // Store name before removing card
            human_.use_mana(card->cost_);
            human_.remove_card_from_hand(choice);
            std::cout << "Played " << creature_name << "!\n";
        }
    } 
    else if (auto* spell = dynamic_cast<Spell*>(card.get())) {
        // Spell card logic
        Player* target = &ai_;
        Creature* creature_target = nullptr;
        
        if (spell->needs_target()) {
            // Target selection
            if (spell->can_target_self()) {
                std::cout << "Target:\n1. Opponent\n2. Yourself\n";
                int target_choice = input_handler_.get_int_input("Select target", 1, 2);
                target = (target_choice == 1) ? &ai_ : &human_;
            }

            // Creature targeting
            if (spell->can_target_creatures() && !target->board().empty()) {
                std::cout << "Select target creature:\n";
                for (size_t i = 0; i < target->board().size(); ++i) {
                    std::cout << i << ": " << target->board()[i]->name_ 
                              << " (" << target->board()[i]->health_ << " HP)\n";
                }
                int creature_choice = input_handler_.get_int_input(
                    "Choose creature (-1 for player)", 
                    -1, 
                    target->board().size() - 1
                );
                if (creature_choice >= 0) {
                    creature_target = target->board()[creature_choice].get();
                }
            }
        }

        std::string spell_name = spell->name_; // Store name before playing
        spell->play(human_, *target, static_cast<void*>(creature_target));
        human_.remove_card_from_hand(choice);
        std::cout << "Cast " << spell_name << "!\n";
    }
    else if (auto* trap = dynamic_cast<Trap*>(card.get())) {
        // Trap card logic
        if (human_.traps().size() >= 3) {
            std::cout << "Maximum traps (3) already set!\n";
            return;
        }
        std::string trap_name = trap->name_; // Store name before playing
        trap->play(human_, ai_);
        human_.remove_card_from_hand(choice);
        std::cout << "Set " << trap_name << " face-down!\n";
    }
    else {
        std::cout << "Unknown card type! This shouldn't happen.\n";
    }
}

void Game::display_hand() const {
    std::cout << "\nYour hand (Mana: " << human_.mana() << "):\n";
    for (size_t i = 0; i < human_.hand().size(); ++i) {
        std::cout << i << ": " << human_.hand()[i]->name_ 
                  << " (" << human_.hand()[i]->cost_ << " mana) - "
                  << "Card" << "\n";
    }
}

void Game::display_game_state() const {
    std::cout << "\n=== Game State ===\n";
    std::cout << "Your Health: " << human_.health() 
              << " | AI Health: " << ai_.health() << "\n";
    std::cout << "Your Mana: " << human_.mana() 
              << "/" << human_.max_mana() 
              << " | AI Mana: " << ai_.mana() 
              << "/" << ai_.max_mana() << "\n\n";
    
    display_boards();
    std::cout << std::endl;
}

void Game::display_boards() const {
    std::cout << "Your creatures:\n";
    for (size_t i = 0; i < human_.board().size(); ++i) {
        auto& c = human_.board()[i];
        std::cout << i << ": " << c->name_ << " (Attack: " 
                  << c->attack_ << ", Health: " << c->health_ << ") "
                  << (c->can_attack_ ? "[READY]" : "[EXHAUSTED]") << "\n";
    }

    std::cout << "\nAI creatures:\n";
    for (size_t i = 0; i < ai_.board().size(); ++i) {
        auto& c = ai_.board()[i];
        std::cout << i << ": " << c->name_ << " (Attack: " 
                  << c->attack_ << ", Health: " << c->health_ << ")\n";
    }
}

// Helper function for Game class
bool Game::validate_target(const Spell& spell, Player& target, Creature* creature) {
    if (spell.needs_target() && !creature && spell.can_target_creatures()) {
        if (target.board().empty()) {
            std::cout << "No valid targets!\n";
            return false;
        }
    }
    return true;
}

void Game::ai_take_turn() {
    Player& ai = ai_;
    Player& human = human_;
    
    std::cout << "\n=== AI's Turn ===" << std::endl;
    
    // AI Decision Making Phase
    bool played_card = false;
    
    // 1. Try to play cards (prioritize creatures, then spells, then traps)
    for (size_t i = 0; i < ai.hand().size() && !played_card; ++i) {
        auto& card = ai.hand()[i];
        
        // Can we afford this card?
        if (ai.mana() < card->cost_) {
            continue;
        }
        
        // Priority 1: Play creatures if we have space
        if (auto* creature = dynamic_cast<Creature*>(card.get())) {
            if (ai.board().size() < 5) {
                std::cout << "AI plays " << creature->name_ << std::endl;
                // Clone the creature to preserve polymorphic behavior
                auto creature_clone = creature->clone();
                if (spawn_creature(std::move(creature_clone), ai)) {
                    ai.use_mana(card->cost_);
                    ai.remove_card_from_hand(i);
                    played_card = true;
                }
            }
        }
        // Priority 2: Play spells
        else if (auto* spell = dynamic_cast<Spell*>(card.get())) {
            std::cout << "AI casts " << spell->name_ << std::endl;
            spell->play(ai, human, static_cast<void*>(nullptr)); // AI doesn't target specific creatures for now
            ai.remove_card_from_hand(i);
            played_card = true;
        }
        // Priority 3: Play traps if we have space
        else if (auto* trap = dynamic_cast<Trap*>(card.get())) {
            if (ai.traps().size() < 3) {
                std::cout << "AI sets " << trap->name_ << " face-down" << std::endl;
                trap->play(ai, human);
                ai.remove_card_from_hand(i);
                played_card = true;
            }
        }
    }
    
    // 2. Attack phase - AI attacks with all ready creatures
    std::cout << "\nAI Attack Phase:" << std::endl;
    

    std::vector<std::pair<Creature*, Creature*>> creature_attacks;
    std::vector<std::pair<Creature*, Player*>> player_attacks;
    
    for (auto& creature : ai.board()) {
        if (creature->can_attack_) {
            if (!human.board().empty()) {
                // Attack weakest enemy creature
                Creature* target = find_weakest_enemy(human);
                if (target) {
                    creature_attacks.push_back({creature.get(), target});
                }
            } else {
                // Attack player directly
                player_attacks.push_back({creature.get(), &human});
            }
        }
    }
    
    
    for (size_t i = 0; i < creature_attacks.size(); ++i) {
        // Check if game is over before each attack
        if (game_over_) {
            break; // Stop processing if game is already over
        }
        
        auto& attack_pair = creature_attacks[i];
        
        // Check for null pointers first
        if (!attack_pair.first || !attack_pair.second) {
            continue; // Skip this attack if either pointer is null
        }
        
        // Check if creatures are still on the board (safer than checking is_alive on potentially freed memory)
        bool attacker_found = false;
        bool defender_found = false;
        
        // Check if attacker is still on AI's board
        for (const auto& creature : ai_.board()) {
            if (creature.get() == attack_pair.first) {
                attacker_found = true;
                break;
            }
        }
        
        // Check if defender is still on human's board
        for (const auto& creature : human_.board()) {
            if (creature.get() == attack_pair.second) {
                defender_found = true;
                break;
            }
        }
        
        if (!attacker_found || !defender_found) {
            continue; // Skip this attack if either creature is no longer on board
        }
        
        // Store names before any checks to avoid use-after-free
        std::string attacker_name = attack_pair.first->name_;
        std::string defender_name = attack_pair.second->name_;
        
        // Check if both creatures are still alive before attacking
        if (!attack_pair.first->is_alive() || !attack_pair.second->is_alive()) {
            continue; 
        }
        
        std::cout << attacker_name << " attacks " << defender_name << std::endl;
        attack(*attack_pair.first, *attack_pair.second);
    }
    
    // Execute player attacks 
    for (size_t i = 0; i < player_attacks.size(); ++i) {
        auto& attack_pair = player_attacks[i];
        std::cout << attack_pair.first->name_ << " attacks you directly!" << std::endl;
        attack_player(*attack_pair.first, *attack_pair.second);
    }
    
    std::cout << "AI ends turn." << std::endl;
}

