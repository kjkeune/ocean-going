//
// Created by kklt on 5/6/25.
//

#include "HealingBarrel.hpp"

#include <iostream>

#include "Config.hpp"

HealingBarrel::HealingBarrel(sf::Vector2f pos, float heal, Island* island): Drop(island) {
    auto& rm = ResourceManager::getInstance();
    sprite.setTexture(rm.getTexture(textures::HEALING_BARREL), true);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    this->heal = heal;
    sound.setBuffer(rm.getSound(sounds::SHIP_HEAL));
    sound.setVolume(60);
}

void HealingBarrel::collect(PlayerShip& ship) {
    auto& rm = ResourceManager::getInstance();
    collectLabel = new Label("+" + std::to_string(static_cast<int>(heal)),fonts::BLACKSHIP, 20, rm.getTexture(textures::HEAL_ICON));
    ship.heal(heal);
    Drop::collect(ship);
    if (DEBUG) std::cout << "Healing Barrel collected!" << std::endl;
}