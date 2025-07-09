//
// Created by kklt on 5/23/25.
//

#include "Ruder.hpp"
#include "Ship.hpp"
#include "../../constants/Colors.hpp"
#include "../../util/Text.hpp"

Ruder::Ruder(Ship *ship, sf::Vector2f pos_offset):
    sprite(ResourceManager::getInstance().getTexture(textures::RUDER))
{
    zIndex = 520;
    this->ship = ship;
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.y * 2, bounds.size.y / 2.f});
    offset = pos_offset;
}

void Ruder::update(float delta) {
    if (ship->disabled) return;
    auto& shipTrans = ship->getTrans();
    sprite.setPosition(shipTrans.getTransform() * (offset + shipTrans.getOrigin()));
    sprite.setScale(shipTrans.getScale());
    sprite.setRotation(shipTrans.getRotation() - sf::degrees(180) - sf::degrees(ship->getTurnAngle()));
}

void Ruder::render(sf::RenderTarget &target) {
    if (ship->disabled) return;
    target.draw(sprite);
}

sf::Transformable &Ruder::getTrans() {
    return sprite;
}

void Ruder::setupTexture(int level) {
    texture.setup(textures::RUDER, {replaceTag(textures::RUDER_TURN, "level", std::to_string(level))});
    sprite.setTexture(texture.getTexture());
}

