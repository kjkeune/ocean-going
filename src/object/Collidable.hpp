//
// Created by kklt on 4/28/25.
//

#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP
#include <vector>

#include "GameObject.hpp"
#include "../util/Shapes.hpp"
#include "SFML/System/Vector2.hpp"

class CollisionHandler;

class Collidable: public GameObject {
public:
    bool contactsNeeded = false;

    virtual void onCollision(Collidable* other, std::vector<sf::Vector2f>& contacts) = 0;
    virtual ConvexPolygon getCollisionBounds() = 0;

    void setActive(bool state) override;
    void destroy() override;

};

#endif //COLLIDABLE_HPP
