//
// Created by kklt on 5/6/25.
//

#include "ShipParts.hpp"

#include <iostream>

#include "Config.hpp"
#include "../../handling/LevelManager.hpp"

ShipParts::ShipParts(sf::Vector2f pos, int amount, Island* island): Drop(island) {
    sprite.setTexture(ResourceManager::getInstance().getTexture(textures::SHIP_PARTS), true);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    this->amount = amount;
}

void ShipParts::collect(PlayerShip& ship) {
    LevelManager::getInstance().addShipParts(amount);
    collectLabel = new Label("+" + std::to_string(amount),fonts::BLACKSHIP, 20, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS_ICON));
    Drop::collect(ship);
    if (DEBUG) std::cout << "Ship Parts collected! +" << amount << std::endl;
}
