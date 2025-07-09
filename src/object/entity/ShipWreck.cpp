//
// Created by kklt on 5/6/25.
//

#include "ShipWreck.hpp"

#include "../../Game.hpp"
#include "../../handling/LevelManager.hpp"
#include "../../handling/ObjectManager.hpp"
#include "../../util/RandomGenerator.hpp"
#include "../../util/Text.hpp"
#include "../drop/HealingBarrel.hpp"
#include "../drop/ShipParts.hpp"

const float ShipWreck::DROP_RADIUS_MIN = 10.f;
const float ShipWreck::DROP_RADIUS_MAX = 50.f;
const float ShipWreck::HEALING_DROP_PROB = 0.4f;
const float ShipWreck::PARTS_DROP_PROB = 1.f;

ShipWreck::ShipWreck(sf::Vector2f pos, sf::Angle ori, int hullType):
    sprite(ResourceManager::getInstance().getTexture(replaceTag(textures::SHIP_WRECK, "type", std::to_string(hullType)))),
    animation(sprite),
    sound(ResourceManager::getInstance().getSound(sounds::SHIP_SINK))
{
    zIndex = 900;
    animation.start();
    this->hullType = hullType;
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    sprite.setRotation(ori);
    bool flipY = RandomGenerator::getInstance().randomBool();
    if (flipY) {
        sprite.setScale({1, -1});
    }
    sound.setPosition({pos.x, 0, pos.y});
    sound.setMinDistance(Game::SOUND_MIN_DIST);
    sound.setVolume(80.f);
    sound.play();
    setActive(true);
}

void ShipWreck::update(float delta) {
    animation.update(delta);
}

void ShipWreck::render(sf::RenderTarget &renderTarget) {
    renderTarget.draw(sprite);
}

sf::Transformable& ShipWreck::getTrans() {
    return sprite;
}

void ShipWreck::dropLoot() {
    auto center = sprite.getPosition();
    auto& rg = RandomGenerator::getInstance();
    auto pos1 = rg.randomPosInRadius(DROP_RADIUS_MIN, DROP_RADIUS_MAX, center);
    if (rg.randomChoice(HEALING_DROP_PROB)) {
        float heal = LevelManager::getInstance().determineHealAmount();
        auto hb = new HealingBarrel(pos1, heal);
        hb->setActive(true);
    }
    auto dir1 = center - pos1;
    float ori1 = std::atan2(dir1.y, dir1.x);
    auto pos2 = rg.randomPosInRadius(DROP_RADIUS_MIN, DROP_RADIUS_MAX, center, ori1 - M_PI_2, ori1 + M_PI_2);
    if (rg.randomChoice(PARTS_DROP_PROB)) {
        auto sp = new ShipParts(pos2, 1);
        sp->setActive(true);
    }
}