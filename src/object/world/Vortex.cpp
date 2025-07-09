//
// Created by kklt on 4/30/25.
//

#include "Vortex.hpp"

#include "../../handling/LevelManager.hpp"
#include "../../handling/SceneLoader.hpp"
#include "../ship/PlayerShip.hpp"

const float Vortex::ROTATION_ANGLE_PER_SEC = 38.f;

Vortex::Vortex(sf::Vector2f pos):
    sprite(ResourceManager::getInstance().getTexture(textures::VORTEX)),
    sound(ResourceManager::getInstance().getSound(sounds::VORTEX))
{
    zIndex = 990;
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    auto size = sprite.getLocalBounds().size;
    float f = 0.33f;
    bounds.push_back(sprite.getTransform() * sf::Vector2f({size.x * f, size.y * f}));
    bounds.push_back(sprite.getTransform() * sf::Vector2f({size.x - size.x * f, size.y * f}));
    bounds.push_back(sprite.getTransform() * sf::Vector2f({size.x - size.x * f, size.y - size.y * f}));
    bounds.push_back(sprite.getTransform() * sf::Vector2f({size.x * f, size.y - size.y * f}));
    sound.setPosition({pos.x, 0, pos.y});
    sound.setMinDistance(Game::SOUND_MIN_DIST);
    sound.setAttenuation(5.f);
    sound.setVolume(100.f);
    sound.setLooping(true);
};

void Vortex::update(float delta) {
    sprite.rotate(sf::degrees(ROTATION_ANGLE_PER_SEC * delta));
}

void Vortex::render(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Transformable& Vortex::getTrans() {
    return sprite;
}

void Vortex::setActive(bool state) {
    if (state) {
        sound.play();
    }
    else {
        sound.stop();
    }
    Collidable::setActive(state);
}


void Vortex::onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) {

}

ConvexPolygon Vortex::getCollisionBounds() {
    return bounds;
}