#ifndef ELEMENTAL_RIFT_HPP
#define ELEMENTAL_RIFT_HPP
class ElementalRift : public Spell {
public:
    ElementalRift() : Spell("Elemental Rift", 5, 
        [](Player& owner, Player& opponent) {
            int fire_air_pairs = 0;
            for (const auto& c : owner.board_) {
                if (c->element_ == Element::Fire || c->element_ == Element::Air) {
                    fire_air_pairs++;
                }
            }
            int damage = 2 + (fire_air_pairs / 2); // +1 per pair
            opponent.modify_health(-damage);
        }) {}
};
#endif
