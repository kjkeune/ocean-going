//
// Created by kklt on 4/28/25.
//

#include "CollisionHandler.hpp"

#include <iostream>
#include <ostream>

#include "../Game.hpp"

CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler& CollisionHandler::getInstance() {
    if (instance == nullptr) {
        instance = new CollisionHandler();
    }
    return *instance;
}

void CollisionHandler::registerObj(Collidable *obj) {
    objects.insert(obj);
}

void CollisionHandler::removeObj(Collidable *obj) {
    objects.erase(obj);
}

void CollisionHandler::handleCollision() {
    // setup vector for indexing and non changing datastructure
    std:std::vector<Collidable*> objs;
    for (auto obj : objects) {
        objs.push_back(obj);
    }
    // check for collision pairwise
    for (int i = 0; i < objs.size(); ++i) {
        auto iBounds = objs[i]->getCollisionBounds();
        auto iRect = boundingRect(iBounds.points);
        for (int j = i + 1; j < objs.size(); ++j) {
            auto jBounds = objs[j]->getCollisionBounds();
            auto jRect = boundingRect(jBounds.points);
            // check bounding rect first
            if (!iRect.findIntersection(jRect)) {
                continue;
            }
            // expensive polygon check
            if (!iBounds.intersects(jBounds)) {
                continue;
            }
            // calc contact points if needed
            std::vector<sf::Vector2f> contacts;
            if (objs[i]->contactsNeeded || objs[j]->contactsNeeded) {
                contacts = iBounds.contactPoints(jBounds);
            }
            // handle object collision
            objs[i]->onCollision(objs[j], contacts);
            objs[j]->onCollision(objs[i], contacts);
            //if (DEBUG) std::cout << "Collision between " << objs[i] << " and " << objs[j] << std::endl;
        }
    }
}