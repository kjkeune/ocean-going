//
// Created by kklt on 4/24/25.
//

#include "PlayerShip.hpp"

#include <iostream>

#include "../../handling/LevelManager.hpp"
#include "../../handling/SceneLoader.hpp"
#include "../entity/ShipWreck.hpp"

PlayerShip::PlayerShip(ShipConfiguration& config): Ship(config) {

}

void PlayerShip::sink() {
    std::cout << "PlayerShip destroyed" << std::endl;
    new ShipWreck(hull.getPosition(), hull.getRotation(), hullType);
    setActive(false);
    SceneLoader::getInstance().loadScene(Scene::DEATH_SCREEN);
    LevelManager::getInstance().resetLevel();
}

void PlayerShip::onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) {
    Ship::onCollision(other, contacts);
    if (auto* v = dynamic_cast<Vortex*>(other)) {
        setActive(false);
        SceneLoader::getInstance().loadScene(Scene::COMPLETED_SCREEN);
        LevelManager::getInstance().nextLevel();
    }
    if (dynamic_cast<EnemyShip*>(other) || dynamic_cast<Island*>(other)) {
        collisionDamageFactor++;
    }
}
