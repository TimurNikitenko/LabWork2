#ifndef ELEMENT_UTILS_HPP
#define ELEMENT_UTILS_HPP
#include "element.hpp"
#include <array>
#include <string_view>

namespace ElementUtils {
    // Elemental relationship matrix (attacker vs defender)
    constexpr std::array<std::array<int, 4>, 4> DAMAGE_MODIFIERS = {{
        /* Fire  */ { 0, -1,  0,  2},  // vs Fire/Water/Earth/Air
        /* Water */ { 2,  0, -1,  0},
        /* Earth */ { 0,  2,  0, -1},
        /* Air   */ {-1,  0,  2,  0}
    }};

    // Convert Element to array index (0-3)
    constexpr size_t to_index(Element e) {
        return static_cast<size_t>(e);
    }

    // Single method for all elemental calculations
    constexpr int combat_modifier(Element attacker, Element defender) {
        if (attacker == Element::None || defender == Element::None) return 0;
        return DAMAGE_MODIFIERS[to_index(attacker)][to_index(defender)];
    }

    // Compile-time name lookup
    constexpr std::string_view name(Element e) {
        constexpr std::array names = {"Fire", "Water", "Earth", "Air", "None"};
        return names[to_index(e)];
    }
}
#endif
