//
// Created by kklt on 5/12/25.
//

#include "GameObject.hpp"

#include "../handling/ObjectManager.hpp"

bool GameObject::isActive() {
    return active;
}

void GameObject::setActive(bool state) {
    if (active == state) {
        return;
    }
    if (state == true) {
        ObjectManager::getInstance().registerObj(this);
    }
    else {
        ObjectManager::getInstance().removeObj(this, false);
    }
    active = state;
}

void GameObject::destroy() {
    if (active == true) {
        ObjectManager::getInstance().removeObj(this, true);
    }
    else {
        delete this;
    }
}

