//
// Created by kklt on 4/28/25.
//

#include "EnemyShip.hpp"

#include <cmath>
#include <iostream>

#include "../../handling/LevelManager.hpp"
#include "../../handling/ObjectManager.hpp"
#include "../entity/ShipWreck.hpp"

const float EnemyShip::HOME_RADIUS = 200.f;
const float EnemyShip::FRONTAL_ATTACK_ANGLE = 100.f;
const float EnemyShip::ALIGN_EPSILON = 0.2f;
const float EnemyShip::MIN_DISTANCE = 100.f;

EnemyShip::EnemyShip(ShipConfiguration& config, Island* home): Ship(config) {
    borderDamagePerSec = 0.f;
    healthBar = new HealthBar({60, 9}, this);
    healthBar->zIndex = 470;
    homeIsland = home;
    fightRadius = canRange * 0.85f;
    fireCooldown /= numCannons / 2.f;
    int sailLevel = config.getUpgrade(UpgradeType::SAIL_VELOCITY).getLevel();
    for (auto sail : sails) {
        sail->setupTexture(true, sailLevel);
    }
}

void EnemyShip::sink() {
    auto wreck = new ShipWreck(hull.getPosition(), hull.getRotation(), hullType);
    wreck->dropLoot();
    destroy();
}

void EnemyShip::setActive(bool active) {
    healthBar->setActive(active);
    Ship::setActive(active);
}

void EnemyShip::destroy() {
    healthBar->destroy();
    Ship::destroy();
}

void EnemyShip::onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) {
    Ship::onCollision(other, contacts);
    if (dynamic_cast<PlayerShip*>(other)) {
        collisionDamageFactor++;
    }
}

void EnemyShip::update(float delta) {
    updateCurrentMode();
    switch (currentMode) {
        case EnemyMode::IDLE:
            idleMode();
        break;
        case EnemyMode::HUNT:
            huntMode();
        break;
        case EnemyMode::FIGHT:
            fightMode();
        break;
        case EnemyMode::RETURN:
            returnMode();
        break;
    }
    //avoidCollisionShips();
    avoidCollisionIslands();
    // align with target
    alignWithTarget();
    timeToFire = std::max(0.f, timeToFire - delta);
    adjustSailToTurn();
    Ship::update(delta);
    healthBar->getTrans().setPosition(getTrans().getPosition() - healthBar->getSize() / 2.f);
}

void EnemyShip::updateCurrentMode() {
    EnemyMode newMode;
    auto& player = ObjectManager::getInstance().getPlayer();
    float distPlayer = (player.getTrans().getPosition() - getTrans().getPosition()).length();
    if (distPlayer > sightRadius) {
        float distHome = (homeIsland->getBoundingCircle().center - getTrans().getPosition()).length();
        if (distHome > homeIsland->getBoundingCircle().radius + HOME_RADIUS) {
            newMode = EnemyMode::RETURN;
        }
        else {
            newMode = EnemyMode::IDLE;
        }
    }
    else if (distPlayer > fightRadius) {
        newMode = EnemyMode::HUNT;
    }
    else {
        newMode = EnemyMode::FIGHT;
    }
    if (newMode != currentMode && DEBUG) {
        std::cout << this << " changed mode to " << std::to_string(static_cast<int>(newMode)) << std::endl;
    }
    currentMode = newMode;
}

void EnemyShip::idleMode() {
    setSailState(0);
    sf::Vector2f homeToEnem = getTrans().getPosition() - homeIsland->getBoundingCircle().center;
    targetDir = homeToEnem;
}

void EnemyShip::huntMode() {
    setSailState(MAX_SAIL_STATE);
    auto& player = ObjectManager::getInstance().getPlayer();
    sf::Vector2f enemToPlayer = player.getTrans().getPosition() - getTrans().getPosition();
    targetDir = enemToPlayer;
}

void EnemyShip::fightMode() {
    auto& player = ObjectManager::getInstance().getPlayer();
    sf::Vector2f enemToPlayer = player.getTrans().getPosition() - getTrans().getPosition();
    sf::Vector2f dirEnem = getDirection();
    sf::Vector2f dirPlay = player.getDirection();
    sf::Vector2f ortho1 = enemToPlayer.perpendicular();
    sf::Vector2f ortho2 = -ortho1;
    // ortho1 should always be point in direction of dirEnem
    if (ortho1.dot(dirPlay) < 0) {
        std::swap(ortho1, ortho2);
    }
    // fire cannons if aligned with player
    if (timeToFire <= 0 && cannonsAlignedWithPlayer()) {
        fireCannons();
        timeToFire += fireCooldown;
    }
    // align with ortho1 if behind player
    if (fabs((-enemToPlayer).angleTo(dirPlay).asDegrees()) > FRONTAL_ATTACK_ANGLE / 2) {
        setSailState(2);
        targetDir = ortho1;
    }
    else {
        // if in front of player check if facing towards player
        setSailState(1);
        if (dirEnem.dot(dirPlay) < 0) {
            targetDir = ortho2;
        }
        else {
            targetDir = ortho1;
        }
    }
}

void EnemyShip::returnMode() {
    setSailState(MAX_SAIL_STATE);
    sf::Vector2f enemToHome = homeIsland->getBoundingCircle().center - getTrans().getPosition();
    targetDir = enemToHome;
}

void EnemyShip::avoidCollisionIslands() {
    if (inRange == nullptr) {
        for (auto island : ObjectManager::getInstance().getWorld().getIslands()) {
            if (!isIslandInRange(island)) {
                continue;
            }
            inRange = island;
        }
        return;
    }
    sf::Vector2f enemToIsland = inRange->getBoundingCircle().center - getTrans().getPosition();
    sf::Vector2f ortho = enemToIsland.perpendicular();
    if (ortho.dot(targetDir) < 0) {
        ortho *= -1.f;
    }
    if (targetDir.dot(enemToIsland) > 0) {
        targetDir = ortho;
    }
    if (!isIslandInRange(inRange)) {
        inRange = nullptr;
    }
}

bool EnemyShip::isIslandInRange(Island *island) {
    Circle& islandCirc = island->getBoundingCircle();
    float dist = (islandCirc.center - getTrans().getPosition()).length();
    return dist < islandCirc.radius + MIN_DISTANCE;
}

void EnemyShip::avoidCollisionShips() {
    for (auto other : ObjectManager::getInstance().getEnemies()) {
        if (other == this || !isShipInRange(other)) {
            continue;
        }
        sf::Vector2f dirEnem = getDirection();
        sf::Vector2f enemToOther = other->getTrans().getPosition() - getTrans().getPosition();
        sf::Vector2f ortho = enemToOther.perpendicular();
        if (ortho.dot(dirEnem) < 0) {
            ortho *= -1.f;
        }
        targetDir = ortho;
    }
}

bool EnemyShip::isShipInRange(Ship *ship) {
    float dist = (ship->getTrans().getPosition() - getTrans().getPosition()).length();
    return dist < MIN_DISTANCE;
}


void EnemyShip::adjustSailToTurn() {
    float turn = fabs(getTurnAngle());
    if (turn > maxTurn * 0.6f) {
        decreaseSails();
    }
    if (turn > maxTurn * 0.9f) {
        decreaseSails();
    }
}

void EnemyShip::alignWithTarget() {
    if (targetDir == sf::Vector2f()) {
        return;
    }
    sf::Vector2f dirFacing = getDirection();
    float angle = dirFacing.angleTo(targetDir).asDegrees();
    if (angle > ALIGN_EPSILON) {
        turnAngle(1);
    }
    else if (angle < -ALIGN_EPSILON) {
        turnAngle(-1);
    }
}

bool EnemyShip::cannonsAlignedWithPlayer() {
    auto& player = ObjectManager::getInstance().getPlayer();
    sf::Vector2f enemToPlayer = player.getTrans().getPosition() - getTrans().getPosition();
    sf::Vector2f dirCannons = getDirection().perpendicular();
    float angle1 = enemToPlayer.angleTo(dirCannons).asDegrees();
    float angle2 = enemToPlayer.angleTo(-dirCannons).asDegrees();
    float attack = attackAngle() - ALIGN_EPSILON;
    return angle1 < attack && angle1 > -attack || angle2 < attack && angle2 > -attack;
}

float EnemyShip::attackAngle() {
    auto& player = ObjectManager::getInstance().getPlayer();
    sf::Vector2f enemPos = getTrans().getPosition();
    sf::Vector2f enemToPlayer = player.getTrans().getPosition() - enemPos;
    float maxAngle = 0;
    for (auto& p : player.getCollisionBounds().points) {
        float angle = fabs(enemToPlayer.angleTo(p - enemPos).asDegrees());
        maxAngle = std::max(maxAngle, angle);
    }
    return maxAngle;
}
