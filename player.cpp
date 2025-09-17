#include "player.hpp"
#include "deck.hpp"
#include "spell.hpp"
#include "trap.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Player::Player(std::string name, int health) 
    : name_(std::move(name)), health_(health), mana_(0), max_mana_(0) {}

// Card Management
void Player::draw_card(Deck& deck) {
    if (hand_.size() < 10) {  // Hand limit
        hand_.push_back(deck.draw_card());
    }
}

bool Player::play_card(size_t hand_index, Player& opponent) {
    if (hand_index >= hand_.size() || !can_play(hand_[hand_index]->cost_)) {
        return false;
    }

    auto& card = hand_[hand_index];
    use_mana(card->cost_);

    // Handle different card types
    if (auto* trap = dynamic_cast<Trap*>(card.get())) {
        set_trap(trap);  // Special handling for traps (face-down)
    } else {
        card->play(*this, opponent);  // Polymorphic call for spells/creatures
    }

    hand_.erase(hand_.begin() + hand_index);
    return true;
}

// Mana System
void Player::gain_mana(int amount) {
    max_mana_ = std::min(10, max_mana_ + amount);  // Cap at 10
    mana_ = max_mana_;
}

void Player::use_mana(int amount) {
    mana_ = std::max(0, mana_ - amount);
}

void Player::reset_mana() {
    mana_ = max_mana_;
}

void Player::modify_mana(int amount) {
    mana_ = std::max(0, std::min(10, mana_ + amount));
}

void Player::increase_max_mana(int amount) {
    mana_modifier_ += amount;  // Modify the modifier instead of max_mana directly
    max_mana_ = base_max_mana_ + mana_modifier_;  // Recalculate max_mana
    max_mana_ = std::max(0, max_mana_);  // Ensure non-negative
    mana_ = std::min(mana_, max_mana_);  // Adjust current mana if needed
}

// Combat
void Player::take_damage(int amount) {
    health_ = std::max(0, health_ - amount);
}

void Player::heal(int amount) {
    health_ += amount;
}

// Trap System
void Player::set_trap(Trap* trap) {
    traps_.push_back(trap);
}

void Player::remove_trap(Trap* trap) {
    traps_.erase(
        std::remove(traps_.begin(), traps_.end(), trap),
        traps_.end()
    );
}

void Player::resolve_traps(Player& triggerer) {
    for (auto it = traps_.begin(); it != traps_.end(); ) {
        if ((*it)->check_trigger(triggerer)) {
            (*it)->resolve(*this, triggerer);
            it = traps_.erase(it);  // Remove after triggering
        } else {
            ++it;
        }
    }
}

// Turn Management
void Player::end_turn() {
    // Use index-based iteration to avoid iterator invalidation
    for (size_t i = 0; i < board_.size(); ++i) {
        if (board_[i]) {
            board_[i]->end_turn();  // Reset creature states
        }
    }
}

void Player::remove_card_from_hand(size_t index) {
    if (index < hand_.size()) {
        hand_.erase(hand_.begin() + index);
    }
}

bool Player::remove_from_board(Creature* creature) {
    for (auto it = board_.begin(); it != board_.end(); ++it) {
        if (it->get() == creature) {
            board_.erase(it);
            return true; // Found and removed the creature
        }
    }
    return false; // Creature not found on this player's board
}

void Player::add_to_board(std::unique_ptr<Creature> creature) {
    if (board_.size() < 5) {
        board_.push_back(std::move(creature));
    }
}

// Debug
void Player::print_status() const {
    std::cout << "=== " << name_ << " ===\n"
              << "Health: " << health_ << "\n"
              << "Mana: " << mana_ << "/" << max_mana_ << "\n"
              << "Hand: " << hand_.size() << " cards\n"
              << "Board: " << board_.size() << " creatures\n"
              << "Traps: " << traps_.size() << " set\n";
}
