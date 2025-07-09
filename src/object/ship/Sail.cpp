//
// Created by kklt on 4/26/25.
//

#include "Sail.hpp"

#include <nlohmann/detail/string_utils.hpp>

#include "Ship.hpp"
#include "../../Game.hpp"
#include "../../util/Text.hpp"

Sail::Sail(Ship* ship, sf::Vector2f pos_offset):
    sprite(ResourceManager::getInstance().getTexture(textures::SAIL))
{
    zIndex = 480;
    this->ship = ship;
    offset = pos_offset;
}

void Sail::update(float delta) {
    if (ship->disabled) return;
    auto& shipTrans = ship->getTrans();
    sprite.setPosition(shipTrans.getTransform() * (offset + shipTrans.getOrigin()));
    sprite.setRotation(shipTrans.getRotation());
    sprite.setScale(shipTrans.getScale());
}

void Sail::render(sf::RenderTarget& target) {
    if (ship->disabled) return;
    target.draw(sprite);
}

sf::Transformable& Sail::getTrans() {
    return sprite;
}

void Sail::setSailState(int state) {
    auto texSize = static_cast<sf::Vector2i>(sprite.getTexture().getSize());
    auto size = sf::Vector2i{texSize.x / (Ship::MAX_SAIL_STATE + 1), texSize.y};
    auto pos = sf::Vector2i{state * size.x, 0};
    sprite.setTextureRect({pos, size});
}

void Sail::setupTexture(bool enemy, int level) {
    auto& base = textures::SAIL;
    std::vector<std::string> layers;
    if (enemy) {
        layers.emplace_back(textures::SAIL_ENEMY);
    }
    layers.emplace_back(replaceTag(textures::SAIL_VELOCITY, "level", std::to_string(level)));
    texture.setup(base, layers);
    auto texSize = static_cast<sf::Vector2i>(texture.getSize());
    sprite.setTexture(texture.getTexture());
    sprite.setTextureRect({{0,0},{texSize.x / (Ship::MAX_SAIL_STATE + 1), texSize.y}});
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
}
