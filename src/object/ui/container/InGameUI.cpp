//
// Created by kklt on 5/22/25.
//

#include "InGameUI.hpp"
#include "../FPSDisplay.hpp"
#include "../Minimap.hpp"
#include "../../../handling/SceneLoader.hpp"
#include "../../../handling/LevelManager.hpp"
#include "../../../Game.hpp"

InGameUI::InGameUI():
    Container(Game::RESOLUTION, sf::Color::Transparent)
{
    auto scrSize = Game::RESOLUTION;
    float scrMar = 20.f;
    float eleMar = 10.f;
    auto fpsDis = new FPSDisplay();
    this->addElement(fpsDis);

    // --> health bar
    auto hBar = new HealthBar({550,20});
    hBar->setRelativePosition({scrSize.x * 0.5f - hBar->getSize().x * 0.5f ,scrSize.y - hBar->getSize().y - scrMar});
    this->addElement(hBar);
    playerHealthBar = hBar;
    // --> cannon display
    auto cDis = new CannonDisplay(50);
    cDis->setRelativePosition(sf::Vector2f{scrSize.x * 0.5f,scrSize.y - hBar->getSize().y - cDis->getSize().y - scrMar - eleMar});
    this->addElement(cDis);
    playerCannonDisplay = cDis;
    // --> Minimap
    auto mMap = new Minimap({scrSize.x * 0.2f, scrSize.x * 0.2f});
    mMap->setRelativePosition({scrSize.x - mMap->getSize().x - scrMar, scrMar});
    this->addElement(mMap);
    // --> Labels
    auto goldL = new Label("0", fonts::BLACKSHIP, 24, ResourceManager::getInstance().getTexture(textures::GOLD_ICON));
    goldL->setRelativePosition({scrSize.x * 0.5f + hBar->getSize().x * 0.5f + 3 * eleMar,scrSize.y - hBar->getSize().y - scrMar});
    goldL->getText().setFillColor(sf::Color::White);
    goldL->getText().setStyle(sf::Text::Bold);
    this->addElement(goldL);
    goldLabel = goldL;
    auto partsL = new Label("0", fonts::BLACKSHIP,  24, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS_ICON));
    partsL->setRelativePosition({scrSize.x * 0.5f + hBar->getSize().x * 0.5f + 3 * eleMar ,scrSize.y - 2 * hBar->getSize().y - eleMar - scrMar});
    partsL->getText().setFillColor(sf::Color::White);
    partsL->getText().setStyle(sf::Text::Bold);
    this->addElement(partsL);
    shipPartsLabel = partsL;
}

void InGameUI::update(float delta) {
    auto& lvlManager = LevelManager::getInstance();
    goldLabel->setTextString(std::to_string(lvlManager.getGold()));
    shipPartsLabel->setTextString(std::to_string(lvlManager.getShipParts()));
}


void InGameUI::setActive(bool state) {
    if (state) {
        auto player = &ObjectManager::getInstance().getPlayer();
        playerHealthBar->setShip(player);
        playerCannonDisplay->setShip(player);
    }
    Container::setActive(state);
}

