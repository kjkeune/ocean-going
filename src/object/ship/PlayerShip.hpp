//
// Created by kklt on 4/24/25.
//

#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include "Ship.hpp"

class PlayerShip : public Ship {
public:
    PlayerShip(ShipConfiguration& config);
    void sink() override;
    void onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) override;
};

#endif //PLAYERSHIP_H
