//
// Created by kklt on 4/28/25.
//

#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include <unordered_set>

#include "../object/Collidable.hpp"

class CollisionHandler {
public:
    static CollisionHandler& getInstance();

    void registerObj(Collidable* obj);
    void removeObj(Collidable* obj);
    void handleCollision();

private:
    static CollisionHandler* instance;

    std::unordered_set<Collidable*> objects;
    CollisionHandler() = default;
};

#endif //COLLISIONHANDLER_HPP
