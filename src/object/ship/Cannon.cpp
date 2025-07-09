//
// Created by kklt on 4/26/25.
//

#include "Cannon.hpp"

#include <cmath>

#include "Ship.hpp"
#include "../../Game.hpp"
#include "../../util/Text.hpp"
#include "../entity/CannonBall.hpp"

Cannon::Cannon(Ship* ship, sf::Vector2f pos_offset, bool left):
    sprite(ResourceManager::getInstance().getTexture(textures::CANNON)),
    animation(sprite, 0.9f, false, true),
    sound(ResourceManager::getInstance().getSound(sounds::CANNON_SHOT))
{
    zIndex = 490;
    this->ship = ship;
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    if (left) {
        sprite.setScale({1.f, -1.f});
    }
    this->left = left;
    offset = pos_offset;
    sound.setMinDistance(Game::SOUND_MIN_DIST);
    sound.setVolume(60.f);
}

void Cannon::update(float delta) {
    if (ship->disabled) return;
    auto& shipTrans = ship->getTrans();
    sprite.setPosition(shipTrans.getTransform() * (offset + shipTrans.getOrigin()));
    if (left) {
        sprite.setRotation(shipTrans.getRotation() + sf::degrees(-90.f));
    } else {
        sprite.setRotation(shipTrans.getRotation() + sf::degrees(90.f));
    }
    sprite.setScale(shipTrans.getScale());
    // update reloading
    loadingState -= delta;
    if (loadingState < 0) {
        loadingState = 0;
    }
    animation.update(delta);
    auto pos = shipTrans.getPosition();
    sound.setPosition({pos.x, 0, pos.y});
}

void Cannon::render(sf::RenderTarget& target) {
    if (ship->disabled) return;
    if (animation.isRunning()) {
        target.draw(sprite, &animation.getShader());
    } else {
        target.draw(sprite);
    }
}

sf::Transformable& Cannon::getTrans() {
    return sprite;
}

void Cannon::fire() {
    if (!isLoaded()) {
        return;
    }
    // determine dir and vel of cannonBall by ship and cannonBall vel
    auto oriCan = sprite.getRotation().asRadians();
    auto dirCan = sf::Vector2f(std::cos(oriCan), sin(oriCan));
    auto velCb = dirCan * velShot + ship->getVelocity();
    auto* cb = new CannonBall(ship->canDamage, ship->canRange, velCb);
    cb->getTrans().setPosition(sprite.getTransform() * (sf::Vector2f({sprite.getLocalBounds().size.x / 2.f, 0.f}) + sprite.getOrigin()));
    loadingState = ship->canReloadTime;
    animation.start();
    sound.play();
}

bool Cannon::isLoaded() {
    return loadingState == 0;
}

void Cannon::setupTexture(int lvlStrength, int lvlRange, int lvlReload) {
    auto& base = textures::CANNON;
    std::vector<std::string> layers;
    layers.emplace_back(replaceTag(textures::CANNON_RANGE, "level", std::to_string(lvlRange)));
    layers.emplace_back(replaceTag(textures::CANNON_STRENGTH, "level", std::to_string(lvlStrength)));
    layers.emplace_back(replaceTag(textures::CANNON_RELOAD, "level", std::to_string(lvlReload)));
    texture.setup(base, layers);
    sprite.setTexture(texture.getTexture());
}
