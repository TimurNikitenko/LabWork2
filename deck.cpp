#include "deck.hpp"
#include "creature.hpp"
#include "spell.hpp"
#include "trap.hpp"
#include "basilisk.hpp"
#include "dragon.hpp"
#include "fairy.hpp"
#include "golem.hpp"
#include "griffin.hpp"
#include "phoenix.hpp"
#include "shadow_mage.hpp"
#include "siren.hpp"
#include "troll.hpp"
#include "wizard.hpp"
#include "fireball.hpp"
#include "heal.hpp"
#include "lightning_bolt.hpp"
#include "mana_surge.hpp"
#include "mirror_force.hpp"
#include "elemental_barrier.hpp"
#include "element.hpp"
#include <iostream>

// Initialize with all game cards
Deck::Deck() {
    // Seed RNG
    std::random_device rd;
    rng_.seed(rd());

    // Add creatures (3 copies of each)
    for (int i = 0; i < 3; ++i) {
        cards_.push_back(std::make_unique<Basilisk>());
        cards_.push_back(std::make_unique<Dragon>());
        cards_.push_back(std::make_unique<Fairy>());
        cards_.push_back(std::make_unique<Golem>());
        cards_.push_back(std::make_unique<Griffin>());
        cards_.push_back(std::make_unique<Phoenix>());
        cards_.push_back(std::make_unique<ShadowMage>());
        cards_.push_back(std::make_unique<Siren>());
        cards_.push_back(std::make_unique<Troll>());
        cards_.push_back(std::make_unique<Wizard>());
    }
    
    // Add spells (2 copies of each)
    for (int i = 0; i < 2; ++i) {
        cards_.push_back(std::make_unique<Fireball>());
        cards_.push_back(std::make_unique<Heal>());
        cards_.push_back(std::make_unique<LightningBolt>());
        cards_.push_back(std::make_unique<ManaSurge>());
    }
    
    // Add traps (1 copy of each)
    cards_.push_back(std::make_unique<MirrorForce>());
    cards_.push_back(std::make_unique<ElementalBarrier>(Element::Fire));
    cards_.push_back(std::make_unique<ElementalBarrier>(Element::Water));
    cards_.push_back(std::make_unique<ElementalBarrier>(Element::Earth));
    cards_.push_back(std::make_unique<ElementalBarrier>(Element::Air));

    shuffle();  // Shuffle initially
}

std::unique_ptr<Card> Deck::draw_card() {
    if (cards_.empty()) {
        return nullptr;  // Empty deck
    }
    
    auto card = std::move(cards_.back());
    cards_.pop_back();
    return card;
}

// Fisher-Yates shuffle
void Deck::shuffle() {
    for (size_t i = 0; i < cards_.size(); ++i) {
        std::uniform_int_distribution<size_t> dist(i, cards_.size() - 1);
        size_t swapIdx = dist(rng_);
        std::swap(cards_[i], cards_[swapIdx]);
    }
}

// Draw top card
std::unique_ptr<Card> Deck::drawCard() {
    if (isEmpty()) {
        refillFromDiscard();
    }

    if (!cards_.empty()) {
        auto card = std::move(cards_.back());
        cards_.pop_back();
        return card;
    }
    return nullptr;  // Empty after refill
}

// Add to discard pile
void Deck::discard(std::unique_ptr<Card> card) {
    discard_pile_.push_back(std::move(card));
}

// Move discard pile back to deck
void Deck::refillFromDiscard() {
    for (auto& card : discard_pile_) {
        cards_.push_back(std::move(card));
    }
    discard_pile_.clear();
    shuffle();
}

// Status checks
bool Deck::isEmpty() const { return cards_.empty(); }
size_t Deck::remainingCards() const { return cards_.size(); }

// Debug
void Deck::printDeck() const {
    std::cout << "Deck (" << cards_.size() << "):\n";
    for (const auto& card : cards_) {
        std::cout << "- " << card->name_ << "\n";
    }
}
