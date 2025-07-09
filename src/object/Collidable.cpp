//
// Created by kklt on 5/15/25.
//
#include "Collidable.hpp"

#include "../handling/CollisionHandler.hpp"

void Collidable::setActive(bool state) {
    if (isActive() != state) {
        if (state == true) {
            CollisionHandler::getInstance().registerObj(this);
        }
        else {
            CollisionHandler::getInstance().removeObj(this);
        }
    }
    GameObject::setActive(state);
}

void Collidable::destroy() {
    if (isActive() == true) {
        CollisionHandler::getInstance().removeObj(this);
    }
    GameObject::destroy();
}

