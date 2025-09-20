#ifndef CARD_HPP
#define CARD_HPP
#include <string>

class Player;  // Forward declaration

class Card {
public:
    Card(std::string name, int cost) 
        : name_(std::move(name)), cost_(cost) {}
    
    virtual ~Card() = default;
    
    // Core (no trivial getters)
    virtual void play(Player& owner, Player& opponent, void* target = nullptr) = 0;
    virtual bool needs_target() const { return false; }
    virtual bool can_target_self() const { return false; }
    virtual bool can_target_creatures() const { return false; }
    
    // Direct access (no getters)
    std::string name_;
    int cost_;
    bool is_face_down = false;  // Public for traps
};
#endif
