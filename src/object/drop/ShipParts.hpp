//
// Created by kklt on 5/6/25.
//

#ifndef SHIPPARTS_HPP
#define SHIPPARTS_HPP
#include "Drop.hpp"

class ShipParts: public Drop {
public:
    ShipParts(sf::Vector2f pos, int amount, Island* island = nullptr);

private:
    int amount = 1;

    void collect(PlayerShip& ship) override;
};

#endif //SHIPPARTS_HPP
