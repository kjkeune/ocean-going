//
// Created by kklt on 5/4/25.
//

#ifndef TREASURE_HPP
#define TREASURE_HPP
#include "Drop.hpp"

class Treasure: public Drop {
public:
    Treasure(sf::Vector2f pos, int amount, Island* island = nullptr);

private:
    int amount;

    void collect(PlayerShip& ship) override;
};

#endif //TREASURE_HPP
