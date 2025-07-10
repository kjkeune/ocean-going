//
// Created by kklt on 4/27/25.
//

#include "CannonBall.hpp"

#include <iostream>

#include "../../handling/ObjectManager.hpp"
#include "../drop/Drop.hpp"
#include "Effect.hpp"
#include "Config.hpp"
#include "../../util/RandomGenerator.hpp"

const float CannonBall::DAMAGE_DEVIATION = 0.1f;
const float CannonBall::CRITICAL_DAMAGE = 2.f;
const float CannonBall::CRITICAL_RANGE_POR = 0.2f;

CannonBall::CannonBall(float damage, float range, sf::Vector2f velocity):
    sprite(ResourceManager::getInstance().getTexture(textures::CANNON_BALL)),
    sound(ResourceManager::getInstance().getSound(sounds::CANNON_BALL_SWOOSH))
{
    zIndex = 600;
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    float deviation = DAMAGE_DEVIATION * damage;
    this->damage = damage + RandomGenerator::getInstance().randomFloat(-deviation,deviation);
    this->range = range;
    this->rangeLeft = range;
    velCurrent = velocity;
    Collidable::setActive(true);
    sound.setMinDistance(75);
    sound.setAttenuation(20.f);
    sound.setVolume(50.f);
    sound.setLooping(true);
}

void CannonBall::update(float delta) {
    auto offset = velCurrent.length() * delta;
    sprite.move(velCurrent * delta);
    rangeLeft -= offset;
    if (!isCritical && rangeLeft / range <= CRITICAL_RANGE_POR) {
        damage *= CRITICAL_DAMAGE;
        isCritical = true;
    }
    if (rangeLeft < 0.f) {
        miss();
    }
    auto pos = sprite.getPosition();
    sound.setPosition({pos.x, 0, pos.y});
    if (sound.getStatus() != sf::Sound::Status::Playing && rangeLeft < range - 50) {
        sound.play();
    }
}

void CannonBall::render(sf::RenderTarget &target) {
    target.draw(sprite);
}

void CannonBall::onCollision(Collidable* other, std::vector<sf::Vector2f>& contacts) {
    if (dynamic_cast<Border*>(other) || dynamic_cast<Vortex*>(other) || dynamic_cast<Drop*>(other)) {
        return;
    }
    hit();
}

ConvexPolygon CannonBall::getCollisionBounds() {
    auto bounds = rectToPoints(sprite.getGlobalBounds());
    return {bounds};
}

sf::Transformable& CannonBall::getTrans() {
    return sprite;
}

void CannonBall::hit() {
    auto effect = new Effect(EffectType::CANNON_BALL_HIT);
    auto& trans = effect->getTrans();
    trans.setPosition(sprite.getPosition());
    sound.stop();
    if (DEBUG && isCritical) std::cout << "Critical Hit!" << std::endl;
    destroy();
}

void CannonBall::miss() {
    auto effect = new Effect(EffectType::CANNON_BALL_MISS);
    auto& trans = effect->getTrans();
    trans.setPosition(sprite.getPosition());
    sound.stop();
    destroy();
}