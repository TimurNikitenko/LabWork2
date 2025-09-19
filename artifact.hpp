#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP
#include "card.hpp"

class Artifact : public Card {
public:
    Artifact(std::string name, int cost, std::string description) 
        : Card(std::move(name), cost), description_(std::move(description)) {}
    
    virtual ~Artifact() = default;
    
    // Artifacts provide persistent effects
    virtual void on_turn_start(Player& owner) { (void)owner; }
    virtual void on_turn_end(Player& owner) { (void)owner; }
    virtual void play(Player& owner, Player& opponent, void* target = nullptr) override {
        // Artifacts are played and stay on the field
        (void)opponent; (void)target;
        on_turn_start(owner);
    }
    
    std::string description_;
};

#endif
