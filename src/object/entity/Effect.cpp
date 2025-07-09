//
// Created by kklt on 5/5/25.
//

#include "Effect.hpp"

#include "../../Game.hpp"
#include "../../handling/ObjectManager.hpp"
#include "../../util/RandomGenerator.hpp"

Effect::Effect(EffectType type):
    sprite(ResourceManager::getInstance().getTexture(textures::CANNON_BALL_MISS)),
    animation(sprite),
    sound(ResourceManager::getInstance().getSound(sounds::CANNON_BALL_MISS))
{
    this->type = type;
    if (type == EffectType::CANNON_BALL_MISS) {
        zIndex = 650;
        sprite.setTexture(ResourceManager::getInstance().getTexture(textures::CANNON_BALL_MISS));
        sound.setBuffer(ResourceManager::getInstance().getSound(sounds::CANNON_BALL_MISS));
        sound.setVolume(70.f);
        animation.setDuration(1.f);
    }
    else if (type == EffectType::CANNON_BALL_HIT) {
        zIndex = 300;
        sprite.setTexture(ResourceManager::getInstance().getTexture(textures::CANNON_BALL_HIT));
        sound.setBuffer(ResourceManager::getInstance().getSound(sounds::CANNON_BALL_HIT));
        sound.setVolume(85.f);
        animation.setDuration(1.2f);
    }
    animation.start();
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    auto& rg = RandomGenerator::getInstance();
    sprite.setRotation(rg.randomAngle());
    bool flipX = rg.randomBool();
    bool flipY = rg.randomBool();
    sprite.setScale({flipX ? -1.f : 1.f,flipY ? -1.f : 1.f});
    sound.setMinDistance(Game::SOUND_MIN_DIST);
    sound.play();
    setActive(true);
}


void Effect::update(float delta) {
    animation.update(delta);
    if (!animation.isRunning() && sound.getStatus() != sf::Sound::Status::Playing) {
        destroy();
    }
    auto pos = sprite.getPosition();
    sound.setPosition({pos.x, 0 , pos.y});
}

void Effect::render(sf::RenderTarget &target) {
    target.draw(sprite, &animation.getShader());
}

sf::Transformable &Effect::getTrans() {
    return sprite;
}


