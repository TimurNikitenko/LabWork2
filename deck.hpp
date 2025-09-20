#ifndef DECK_HPP
#define DECK_HPP
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "card.hpp"

class Deck {
public:
    Deck();
    
    // ---------- Core ----------
    void shuffle();
    std::unique_ptr<Card> draw_card();
    std::unique_ptr<Card> drawCard();
    
    void discard(std::unique_ptr<Card> card);
    
    // ---------- Helpers ----------
    bool empty() const { return cards_.empty() && discard_pile_.empty(); }
    bool isEmpty() const;
    size_t remainingCards() const;
    void printDeck() const;
    void refillFromDiscard();

private:
    std::vector<std::unique_ptr<Card>> cards_;
    std::vector<std::unique_ptr<Card>> discard_pile_;
    std::mt19937 rng_{std::random_device{}()};
    
    void refill_from_discard() {
        cards_ = std::move(discard_pile_);
        shuffle();
    }
};
#endif
