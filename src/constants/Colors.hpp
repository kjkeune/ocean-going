//
// Created by kklt on 5/15/25.
//

#ifndef COLORS_HPP
#define COLORS_HPP
#include "SFML/Graphics/Color.hpp"

namespace colors {
    inline constexpr auto BORDER_OVERLAY = sf::Color(0, 0, 0, 50);
    inline constexpr auto SHIP_BROWN = sf::Color(139, 103, 74);
    inline constexpr auto SHIP_BROWN_DARK = sf::Color(80, 60, 44);
    inline constexpr auto HEALTH_RED = sf::Color(155, 27, 26);
    inline constexpr auto HEALTH_RED_LIGHT = sf::Color(255, 180, 180);
    inline constexpr auto HEALTH_RED_DARK = sf::Color(88, 44, 44);
    inline constexpr auto HEALTH_RED_DARK_TRANS = sf::Color(88, 44, 44, 70);
    inline constexpr auto MAP_WHITE = sf::Color(247, 235, 208);
    inline constexpr auto MAP_WHITE_TRANS = sf::Color(247, 235, 208, 125);
    inline constexpr auto MAP_WHITE_GREY = sf::Color(230, 223, 208);
    inline constexpr auto MAP_WHITE_DARK = sf::Color(234, 221, 191);
    inline constexpr auto MAP_SELECTED = sf::Color(224, 181, 85);
    inline constexpr auto MAP_SELECTED_RED = sf::Color(255, 85, 85);
    inline constexpr auto TEXT_GREY = sf::Color(115, 115, 115);
    inline constexpr auto STATS_GREY = sf::Color(115, 115, 115);
    inline constexpr auto STATS_GREY_LIGHT = sf::Color(170, 170, 170);
    inline constexpr auto MINIMAP_GRID_GREY = sf::Color(102, 102, 102);
    inline constexpr auto MINIMAP_ISLAND_GREY = sf::Color(240, 240, 240);
}

#endif //COLORS_HPP
