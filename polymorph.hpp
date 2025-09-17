#ifndef POLYMORPH_HPP
#define POLYMORPH_HPP
class Polymorph : public Spell {
public:
    Polymorph() : Spell("Polymorph", 3, [](Player& owner, Player& opponent) {
        if (!opponent.board_.empty()) {
            auto& target = opponent.board_.back(); // Target last played creature
            target = std::make_unique<Creature>("Sheep", 0, 1, 1, Element::Earth);
        }
    }) {}
};
#endif
