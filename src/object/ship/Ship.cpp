//
// Created by kklt on 4/24/25.
//

#include "Ship.hpp"
#include <cmath>
#include <iostream>

#include "../../Game.hpp"
#include "../../handling/ObjectManager.hpp"
#include "../entity/CannonBall.hpp"
#include "../../constants/Paths.hpp"
#include "../../util/MultiLayerTexture.hpp"
#include "../../util/Text.hpp"
#include "../../util/RandomGenerator.hpp"

const int Ship::MAX_SAIL_STATE = 3;

std::unordered_map<int, std::vector<sf::Vector2f>> Ship::TYPE_BOUNDS = {
    {1,{
            {2.f, 11.f}, {4.f, 7.f}, {21.f, 2.f}, {50.f, 2.f}, {72.f, 9.f}, {84.f, 20.f},
            {72.f, 31.f}, {50.f, 38.f}, {21.f, 38.f}, {4.f, 33.f}, {2.f, 29.f}}},
    {2, {
            {2.f, 14.f}, {5.f, 9.f}, {29.f, 2.f}, {66.f, 2.f}, {94.f, 10.f}, {109.f, 23.f},
            {94.f, 36.f}, {66.f, 44.f}, {29.f, 44.f}, {5.f, 37.f}, {2.f, 32.f}}},
    {3, {
            {2.f, 19.f}, {6.f, 9.f}, {35.f, 2.f}, {83.f, 2.f}, {114.f, 10.f}, {136.f, 26.f},
            {114.f, 42.f}, {83.f, 50.f}, {35.f, 50.f}, {6.f, 43.f}, {2.f, 33.f}}},
};

Ship::Ship(ShipConfiguration& config):
    hull(ResourceManager::getInstance().getTexture(replaceTag(textures::HULL, "type", std::to_string(config.getUpgrade(UpgradeType::HULL).getLevel())))),
    soundDamage(ResourceManager::getInstance().getSound(sounds::CANNON_SHOT)),
    soundSail(ResourceManager::getInstance().getSound(sounds::CANNON_SHOT)),
    soundHull(ResourceManager::getInstance().getSound(sounds::CANNON_SHOT))
{
    contactsNeeded = true;
    zIndex = 500;
    config.applyAll(this);
    health = maxHealth;
    borderDamagePerSec = maxHealth * 0.15f;
    initHull(config);
    initSails(config);
    initCannons(config);
    initRuder(config);
    soundDamage.setMinDistance(Game::SOUND_MIN_DIST);
    soundDamage.setVolume(45.f);
    soundSail.setMinDistance(Game::SOUND_MIN_DIST);
    soundSail.setVolume(75.f);
    soundHull.setMinDistance(Game::SOUND_MIN_DIST / 2.f);
    soundHull.setAttenuation(15.f);
    soundHull.setVolume(20.f);
}

void Ship::initHull(ShipConfiguration& config) {
    int hullStrLevel = config.getUpgrade(UpgradeType::HULL_STRENGTH).getLevel();
    auto base = replaceTag(textures::HULL, "type", std::to_string(hullType));
    auto layer = replaceTag(textures::HULL_STRENGTH, "level", std::to_string(hullStrLevel));
    layer = replaceTag(layer,"type", std::to_string(hullType));
    textureHull.setup(base, {layer});
    hull.setTexture(textureHull.getTexture());
    hull.setOrigin(hull.getLocalBounds().getCenter());
    // init collision bounds
    bounds.insert(bounds.end(), TYPE_BOUNDS[hullType].begin(), TYPE_BOUNDS[hullType].end());
}

void Ship::initSails(ShipConfiguration& config) {
    switch (hullType) {
        case 1:
            sails.push_back(new Sail(this, sf::Vector2f({-13.f, 0.f})));
            break;
        case 2:
            if (numSails == 1) {
                sails.push_back(new Sail(this, sf::Vector2f({-14.f, 0.f})));
            }
            else {
                sails.push_back(new Sail(this, sf::Vector2f({14.f, 0.f})));
                sails.push_back(new Sail(this, sf::Vector2f({-28.f, 0.f})));
            }
            break;
        case 3:
            if (numSails == 1) {
                sails.push_back(new Sail(this, sf::Vector2f({-7.f, 0.f})));
            }
            else if (numSails == 2) {
                sails.push_back(new Sail(this, sf::Vector2f({-42.f, 0.f})));
                sails.push_back(new Sail(this, sf::Vector2f({8.f, 0.f})));
            }
            else {
                sails.push_back(new Sail(this, sf::Vector2f({-7.f, 0.f})));
                sails.push_back(new Sail(this, sf::Vector2f({-42.f, 0.f})));
                sails.push_back(new Sail(this, sf::Vector2f({28.f, 0.f})));
            }
            break;
    }
    int sailLevel = config.getUpgrade(UpgradeType::SAIL_VELOCITY).getLevel();
    for (auto sail : sails) {
        sail->setupTexture(false, sailLevel);
    }
}

void Ship::initCannons(ShipConfiguration& config) {
    switch (hullType) {
        case 1:
            cannons.push_back(new Cannon(this, sf::Vector2f({5.f, -27.f}), true));
            cannons.push_back(new Cannon(this, sf::Vector2f({5.f, 27.f}), false));
            break;
        case 2:
            if (numCannons == 2) {
                cannons.push_back(new Cannon(this, sf::Vector2f({8.f, -30.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({8.f, 30.f}), false));
            }
            else {
                cannons.push_back(new Cannon(this, sf::Vector2f({-16.f, -30.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-16.f, 30.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({8.f, -30.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({8.f, 30.f}), false));
            }
            break;
        case 3:
            if (numCannons == 2) {
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, 33.f}), false));
            }
            else if (numCannons == 4) {
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({14.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({14.f, 33.f}), false));
            }
            else if (numCannons == 6) {
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({14.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({14.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({-34.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-34.f, 33.f}), false));
            }
            else {
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-10.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({5.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({5.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({20.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({20.f, 33.f}), false));
                cannons.push_back(new Cannon(this, sf::Vector2f({-34.f, -33.f}), true));
                cannons.push_back(new Cannon(this, sf::Vector2f({-34.f, 33.f}), false));
            }
            break;
    }
    int cannonStrLevel = config.getUpgrade(UpgradeType::CANNON_STRENGTH).getLevel();
    int cannonRanLevel = config.getUpgrade(UpgradeType::CANNON_RANGE).getLevel();
    int cannonRelLevel = config.getUpgrade(UpgradeType::CANNON_RELOADING).getLevel();
    for (auto cannon : cannons) {
        cannon->setupTexture(cannonStrLevel, cannonRanLevel, cannonRelLevel);
    }
}

void Ship::initRuder(ShipConfiguration& config) {
    int ruderLevel = config.getUpgrade(UpgradeType::RUDER_TURN).getLevel();
    ruder = new Ruder(this,{-hull.getLocalBounds().size.x / 2.f, 0});
    ruder->setupTexture(ruderLevel);
}

void Ship::update(float delta) {
    if (disabled) return;
    // Deal border damage
    if (isOutsideBorder) {
        damage(borderDamagePerSec * delta);
        isOutsideBorder = false;
    }
    // Collision handling
    if (isInCollision) {
        damage(collisionDamageFactor * collisionDamagePerSec * delta);
        pushVelCurrent *= pushVelPerSec * delta;
        isInCollision = false;
        collisionDamageFactor = 0;
    }
    if (pushVelCurrent.length() > 0.f) {
        float factor = 1 - velIncPerSec * delta / pushVelCurrent.length();
        if (factor < 0.f) {
            pushVelCurrent = {0.f,0.f};
        } else {
            pushVelCurrent *= factor;
        }
    }
    // Set turning angle
    float turnPerUpd = turnPerSec * delta * static_cast<float>((turn > 0) - (turn < 0));
    if (turn > 0) {
        turn = std::max(turn - turnPerUpd, 0.f);
    }
    else {
        turn = std::min(turn - turnPerUpd, 0.f);
    }
    // Rotate Ship
    hull.rotate(sf::degrees(turnPerUpd));
    auto dirHeading = getDirection();
    // Set Velocity
    velCurrent = dirHeading * velCurrent.length();
    if (velCurrent.length() < vel) {
        velCurrent += dirHeading * velIncPerSec * delta;
        if (velCurrent.length() > vel) {
            velCurrent = dirHeading * vel;
        }
    }
    else if (velCurrent.length() > vel) {
        velCurrent -= dirHeading * velIncPerSec * delta;
        if (velCurrent.dot(dirHeading) < 0.f) {
            velCurrent = {0.f,0.f};
        }
    }
    // Move the ship
    hull.move(velCurrent * delta + pushVelCurrent);
    // sound
    auto pos = hull.getPosition();
    sf::Vector3f soundPos(pos.x,0,pos.y);
    soundDamage.setPosition(soundPos);
    soundSail.setPosition(soundPos);
    soundHull.setPosition(soundPos);
    if (soundHull.getStatus() != sf::Sound::Status::Playing) {
        auto& rm = ResourceManager::getInstance();
        auto& rg = RandomGenerator::getInstance();
        sf::SoundBuffer* buffer;
        if (sailState >= 3) {
            buffer = &rm.getSound(replaceTag(sounds::WAVES_HULL_HARD, "id", std::to_string(rg.randomInt(0,3))));
        }
        else if (sailState >= 1) {
            buffer = &rm.getSound(replaceTag(sounds::WAVES_HULL_MEDIUM, "id", std::to_string(rg.randomInt(0,2))));
        }
        else {
            buffer = &rm.getSound(replaceTag(sounds::WAVES_HULL_CALM, "id", std::to_string(rg.randomInt(0,2))));
        }
        soundHull.setBuffer(*buffer);
        soundHull.play();
    }
}

void Ship::render(sf::RenderTarget& target) {
    if (disabled) return;
    target.draw(hull);
}

sf::Transformable& Ship::getTrans() {
    return hull;
}

void Ship::onCollision(Collidable* other, std::vector<sf::Vector2f>& contacts) {
    if (disabled) return;
    if (dynamic_cast<Ship*>(other) || dynamic_cast<Island*>(other)) {
        isInCollision = true;
        auto cmid = centerPoint(contacts);
        auto dirPush = getCollisionBounds().center - cmid;
        if (dirPush.length() > 0.f) {
            dirPush /= dirPush.length();
        }
        pushVelCurrent = dirPush;
    }
    else if (auto* cb = dynamic_cast<CannonBall*>(other)) {
        damage(cb->damage);
    }
    else if (auto b = dynamic_cast<Border*>(other)) {
        isOutsideBorder = true;
    }
}

ConvexPolygon Ship::getCollisionBounds() {
    std::vector<sf::Vector2f> bt;
    for (auto& p : bounds) {
        bt.push_back(hull.getTransform() * p);
    }
    return {bt};
}

int Ship::getSailState() {
    return sailState;
}

sf::Vector2f Ship::getVelocity() {
    return velCurrent;
}

sf::Vector2f Ship::getDirection() {
    float ori = hull.getRotation().asRadians();
    return {cosf(ori), sinf(ori)};
}

float Ship::determineVelocity(int sailState) {
    float velSail = velPerSailState * static_cast<float>(sailState);
    return velSail + 0.25f * velSail * (numSails - 1);
}

void Ship::setSailState(int state) {
    if (sailState == state || state < 0 || state > MAX_SAIL_STATE) {
        return;
    }
    sailState = state;
    for (auto& sail : sails) {
        sail->setSailState(sailState);
    }
    vel = determineVelocity(sailState);
    soundSail.stop();
    auto& rm = ResourceManager::getInstance();
    auto& rg = RandomGenerator::getInstance();
    soundSail.setBuffer(rm.getSound(replaceTag(sounds::SAIL_DEPLOY, "id", std::to_string(rg.randomInt(0,2)))));
    soundSail.play();
}

void Ship::increaseSails() {
    setSailState(getSailState() + 1);
}

void Ship::decreaseSails() {
    setSailState(getSailState() - 1);
}

float Ship::getTurnAngle() {
    return turn;
}

void Ship::turnAngle(float angle) {
    turn += angle;
    if (turn > maxTurn) {
        turn = maxTurn ;
    } else if (turn < -maxTurn) {
        turn = -maxTurn;
    }
}

void Ship::fireCannons() {
    for (int i = 0; i < cannons.size(); i += 2) {
        if (cannons[i]->isLoaded()) {
            cannons[i]->fire();
            cannons[i + 1]->fire();
            break;
        }
    }
}

std::vector<bool> Ship::cannonsLoaded() {
    std::vector<bool> state;
    for (auto& c : cannons) {
        state.push_back(c->isLoaded());
    }
    return state;
}

void Ship::damage(float amount) {
    if (invincible || amount == 0) {
        return;
    }
    health -= amount;

    if (health <= 0) {
        disabled = true;
        sink();
    }
    if (soundDamage.getStatus() != sf::Sound::Status::Playing) {
        auto& rm = ResourceManager::getInstance();
        auto& rg = RandomGenerator::getInstance();
        soundDamage.setBuffer(rm.getSound(replaceTag(sounds::SHIP_DAMAGE, "id", std::to_string(rg.randomInt(0,5)))));
        soundDamage.play();
    }
    if (DEBUG) std::cout << this << " was damaged by " << amount << std::endl;
}

void Ship::heal(float amount) {
    health = std::min(health + amount, maxHealth);
    if (DEBUG) std::cout << this << " was healed by " << amount << std::endl;
}

float Ship::getHealth() {
    return health;
}

void Ship::setActive(bool active) {
    for (auto& sail : sails) {
        sail->setActive(active);
    }
    for (auto& cannon : cannons) {
        cannon->setActive(active);
    }
    ruder->setActive(active);
    Collidable::setActive(active);
}

void Ship::destroy() {
    for (auto& sail : sails) {
        sail->destroy();
    }
    for (auto& cannon : cannons) {
        cannon->destroy();
    }
    ruder->destroy();
    Collidable::destroy();
}