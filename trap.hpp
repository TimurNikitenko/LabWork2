#ifndef TRAP_HPP
#define TRAP_HPP
#include "card.hpp"
#include <functional>

class Trap : public Card {
public:
    Trap(std::string name, int cost);
    
    void play(Player& owner, Player& opponent, void* target = nullptr) override;
    bool check_trigger(const Player& triggerer) const;
    void resolve(Player& owner, Player& triggerer);
};
#endif
