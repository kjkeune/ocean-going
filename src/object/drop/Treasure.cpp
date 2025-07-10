//
// Created by kklt on 5/4/25.
//

#include "Treasure.hpp"
#include <iostream>

#include "../../handling/LevelManager.hpp"
#include "Config.hpp"

Treasure::Treasure(sf::Vector2f pos, int amount, Island* island): Drop(island) {
    sprite.setTexture(ResourceManager::getInstance().getTexture(textures::TREASURE), true);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    this->amount = amount;
}

void Treasure::collect(PlayerShip& ship) {
    LevelManager::getInstance().addGold(amount);
    collectLabel = new Label("+" + std::to_string(amount),fonts::BLACKSHIP, 20, ResourceManager::getInstance().getTexture(textures::GOLD_ICON));
    Drop::collect(ship);
    if (DEBUG) std::cout << "Treasure collected! +" << amount << std::endl;
}