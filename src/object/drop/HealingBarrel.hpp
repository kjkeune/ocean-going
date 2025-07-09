//
// Created by kklt on 5/6/25.
//

#ifndef HEALINGBARREL_HPP
#define HEALINGBARREL_HPP
#include "Drop.hpp"

class HealingBarrel: public Drop {
public:
    HealingBarrel(sf::Vector2f pos, float heal, Island* island = nullptr);

private:
    float heal;

    void collect(PlayerShip& ship) override;
};

#endif //HEALINGBARREL_HPP
