//
// Created by kklt on 4/24/25.
//

#include "ObjectManager.hpp"
#include "../Game.hpp"

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager& ObjectManager::getInstance() {
    if (instance == nullptr) {
        instance = new ObjectManager();
    }
    return *instance;
}

void ObjectManager::registerObj(GameObject* obj) {
    if (auto p = dynamic_cast<PlayerShip*>(obj)) {
        if (player != nullptr && objects.find(player) != objects.end()) {
            toRemove[player] = true;
        }
        player = p;
    }
    else if (auto* w = dynamic_cast<World*>(obj)) {
        world = w;
    }
    else if (auto* e = dynamic_cast<EnemyShip*>(obj)) {
        enemies.insert(e);
    }
    objects.insert(obj);
}

void ObjectManager::removeObj(GameObject *obj, bool deleteObj) {
    if (objects.find(obj) != objects.end() && toRemove.find(obj) == toRemove.end()) {
        toRemove[obj] = deleteObj;
        if (auto* e = dynamic_cast<EnemyShip*>(obj)) {
            enemies.erase(e);
        }
    }
}

void ObjectManager::clear() {
    for (auto* obj : objects) {
        if (toRemove.find(obj) == toRemove.end()) {
            obj->destroy();
        }
    }
}

void ObjectManager::renderAll(sf::RenderTarget& target, sf::View& gameView, sf::View& uiView) {
    target.setView(gameView);
    auto it = objects.begin();
    GameObject* obj = *it;
    // render objects with current view
    while (it != objects.end()) {
        if (obj->zIndex < 0) {
            break;
        }
        obj->render(target);
        obj = *++it;
    }
    // render UI with default view
    target.setView(uiView);
    while (it != objects.end()) {
        obj->render(target);
        obj = *++it;
    }
}

void ObjectManager::updateAll(float delta) {
    for (auto& [obj, deleteObj] : toRemove) {
        objects.erase(obj);
        if (deleteObj) {
            delete obj;
        }
    }
    toRemove.clear();
    for (auto* obj : objects) {
        obj->update(delta);
    }
}

PlayerShip& ObjectManager::getPlayer() {
    return *player;
}

World& ObjectManager::getWorld() {
    return *world;
}

std::vector<EnemyShip*> ObjectManager::getEnemies() {
    std::vector<EnemyShip*> result;
    for (auto enemy : enemies) {
        result.push_back(enemy);
    }
    return result;
}


template<typename T>
std::vector<T *> ObjectManager::getAll() {
    std::vector<T *> result;
    for (auto obj : objects) {
        if (auto p = dynamic_cast<T*>(obj)) {
            result.push_back(p);
        }
    }
    return result;
}
