//
// Created by kklt on 6/10/25.
//

#include "CompletedScreen.hpp"
#include "../../../constants/Colors.hpp"
#include "../../../Game.hpp"
#include "../button/PlankButton.hpp"
#include "../Label.hpp"
#include "../../../handling/LevelManager.hpp"

CompletedScreen::CompletedScreen():
    Container(Game::RESOLUTION, colors::BORDER_OVERLAY),
    sound(ResourceManager::getInstance().getSound(sounds::LEVEL_DONE))
{
    sound.setVolume(75);
    sound.setRelativeToListener(true);
    auto scrSize = Game::RESOLUTION;
    float mar = 100.f;
    float labMar = 20.f;
    // --> Label Level
    auto levelL = new Label("Level 1", fonts::BLACKSHIP,  36);
    levelL->setRelativePosition({scrSize.x / 2.f - levelL->getSize().x / 2.f, mar});
    levelL->getText().setFillColor(sf::Color::White);
    levelLabel = levelL;
    addElement(levelL);
    // --> Label
    auto compL = new Label("Level Completed!", fonts::TREAMD,  110);
    compL->setRelativePosition({scrSize.x / 2.f - compL->getSize().x / 2.f, levelL->getSize().y + mar + labMar});
    compL->getText().setFillColor(sf::Color::White);
    compL->getText().setStyle(sf::Text::Bold);
    addElement(compL);
    // --> Label gold
    auto goldL = new Label("+1000", fonts::BLACKSHIP,  36, ResourceManager::getInstance().getTexture(textures::GOLD_ICON));
    goldL->setRelativePosition({scrSize.x / 2.f - goldL->getSize().x / 2.f, scrSize.y / 2.f + labMar / 2.f});
    goldL->getText().setFillColor(sf::Color::White);
    goldLabel = goldL;
    addElement(goldL);
    // --> Label Parts
    auto partsL = new Label("+10", fonts::BLACKSHIP,  36, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS_ICON));
    partsL->setRelativePosition({scrSize.x / 2.f - goldL->getSize().x / 2.f, scrSize.y / 2.f - partsL->getSize().y - labMar / 2.f});
    partsL->getText().setFillColor(sf::Color::White);
    partsLabel = partsL;
    addElement(partsL);
    // --> Back button
    auto backB = new PlankButton();
    backB->setRelativePosition({scrSize.x / 2.f - backB->getSize().x / 2.f, scrSize.y - backB->getSize().y - mar});
    backB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::SHIP_MENU);
    });
    backB->setTextString("Upgrade Ship");
    this->addElement(backB);
}

void CompletedScreen::setActive(bool state) {
    Container::setActive(state);
    if (state) {
        auto& lm = LevelManager::getInstance();
        int lvl = lm.getLevel();
        levelLabel->setTextString("Level " + std::to_string(lvl));
        int gold = lm.getGold();
        goldLabel->setTextString("+" + std::to_string(gold));
        int parts = lm.getShipParts();
        partsLabel->setTextString("+" + std::to_string(parts));
        sound.play();
    }
}
