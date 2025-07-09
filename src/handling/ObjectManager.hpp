//
// Created by kklt on 4/24/25.
//

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <set>
#include <unordered_set>

#include "../object/ship/EnemyShip.hpp"
#include "../object/ship/PlayerShip.hpp"
#include "../object/world/World.hpp"

struct zComparator {
    bool operator()(const GameObject* a, const GameObject* b) const {
        if (a->zIndex == b->zIndex) {
            return a < b; // fallback to pointer address for uniqueness
        }
        return a->zIndex > b->zIndex; // higher z first for render order
    }
};

class ObjectManager {
public:
    static ObjectManager& getInstance();

    void registerObj(GameObject* obj);
    void removeObj(GameObject* obj, bool deleteObj);
    void clear();
    void renderAll(sf::RenderTarget& target, sf::View& gameView, sf::View& uiView);
    void updateAll(float delta);

    template <typename T>
    std::vector<T*> getAll();
    PlayerShip& getPlayer();
    World& getWorld();
    std::vector<EnemyShip*> getEnemies();

private:
    static ObjectManager* instance;

    ObjectManager() = default;

    std::set<GameObject*, zComparator> objects;
    std::unordered_map<GameObject*, bool> toRemove;
    World* world = nullptr;
    PlayerShip* player = nullptr;
    std::unordered_set<EnemyShip*> enemies;

};

#endif //OBJECTMANAGER_H
