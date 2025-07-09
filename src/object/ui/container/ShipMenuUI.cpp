//
// Created by kklt on 5/22/25.
//

#include "ShipMenuUI.hpp"

#include "../../../handling/SceneLoader.hpp"
#include "../../../Game.hpp"
#include "../Label.hpp"
#include "ShipPreview.hpp"
#include "../../../constants/Colors.hpp"
#include "../../../handling/LevelManager.hpp"
#include "../button/UpgradeButton.hpp"
#include "../button/PlankButton.hpp"

ShipMenuUI::ShipMenuUI():
    Container(Game::RESOLUTION, colors::BORDER_OVERLAY)
{
    auto scrSize = Game::RESOLUTION;
    float scrMargin = 30.f;
    // init background world
    auto viewSize = static_cast<sf::Vector2i>(Game::VIEW_SIZE);
    backgroundWorld = new World({ viewSize.x  / World::TILE_SIZE + 1,  viewSize.y  / World::TILE_SIZE + 1}, {},{-10000,-10000});
    // --> start button
    auto startB = new PlankButton();
    startB->setRelativePosition({scrSize.x * 0.35f - startB->getSize().x / 2.f,scrSize.y - startB->getSize().y - scrMargin});
    startB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::IN_GAME);
    });
    startB->setTextString("Start Next Level");
    this->addElement(startB);
    // --> back button
    auto backB = new PlankButton();
    backB->setRelativePosition({scrSize.x * 0.65f - startB->getSize().x / 2.f,scrSize.y - startB->getSize().y - scrMargin});
    backB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::MAIN_MENU);
    });
    backB->setTextString("Back To Menu");
    this->addElement(backB);
    // --> Map
    auto& mapTex = ResourceManager::getInstance().getTexture(textures::SHIP_MENU_MAP);
    auto map = new Container({scrSize.x * 0.875f, scrSize.y - scrMargin * 2.75f - startB->getSize().y},mapTex);
    map->setRelativePosition({scrSize.x * 0.5f - map->getSize().x / 2.f , scrMargin});
    this->addElement(map);
    // Labels
    auto mapSize = map->getSize();
    float mapMarX = 80.f;
    float mapMarY = 50.f;
    // title
    auto title = new Label("Upgrade Yer Ship",fonts::TREAMD, 34);
    title->setRelativePosition({mapSize.x / 2 - title->getSize().x / 2, mapMarY * 0.75f});
    title->getText().setStyle(sf::Text::Bold);
    map->addElement(title);
    // level
    auto levelL = new Label("Level ",fonts::BLACKSHIP,  22);
    levelL->setRelativePosition({mapMarX,mapMarY});
    map->addElement(levelL);
    levelLabel = levelL;
    // gold
    auto goldL = new Label("100000",fonts::BLACKSHIP,  22, ResourceManager::getInstance().getTexture(textures::GOLD_ICON));
    goldL->setRelativePosition({mapSize.x - mapMarX - goldL->getSize().x, mapMarY});
    map->addElement(goldL);
    goldLabel = goldL;
    // parts
    auto partsL = new Label("100",fonts::BLACKSHIP, 22, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS_ICON));
    partsL->setRelativePosition({mapSize.x - 2.5f * mapMarY - goldL->getSize().x - partsL->getSize().x,mapMarY});
    map->addElement(partsL);
    shipPartsLabel = partsL;
    // Ship Preview
    float interMar = 12.f;
    float porXButt = 0.6f;
    auto preview = new ShipPreview({(map->getSize().x - mapMarX * 2) * (1 - porXButt) - mapMarX / 2.f, map->getSize().y - title->getSize().y - mapMarY * 2 - interMar});
    preview->setRelativePosition({mapMarX,title->getSize().y + mapMarY + interMar});
    map->addElement(preview);
    // Upgrade Buttons
    sf::Vector2f ugbOffset = {map->getSize().x * (1 - porXButt), title->getSize().y + mapMarY + interMar};
    sf::Vector2f upgSize = {(map->getSize().x - ugbOffset.x - mapMarX * 1.2f - interMar) / 2.f, (map->getSize().y - ugbOffset.y - mapMarY * 1.33f) / 5.f - interMar};
    for (int i = 0; i < Upgrade::NUM_UPGRADES; i++) {
        auto upgrade = static_cast<UpgradeType>(i);
        sf::Vector2f upgPos = {ugbOffset.x,  ugbOffset.y + i % 5 * (upgSize.y + interMar)};
        if (i > 4) {
            upgPos += sf::Vector2f(upgSize.x + interMar, 0);
        }
        auto upgB = new UpgradeButton(upgSize, upgrade, preview);
        upgB->setRelativePosition(upgPos);
        map->addElement(upgB);
    }

}

void ShipMenuUI::update(float delta) {
    auto& lvlManager = LevelManager::getInstance();
    goldLabel->setTextString(std::to_string(lvlManager.getGold()));
    shipPartsLabel->setTextString(std::to_string(lvlManager.getShipParts()));
}

void ShipMenuUI::setActive(bool state) {
    Container::setActive(state);
    backgroundWorld->setActive(state);
    if (state) {
        auto& view = Game::getInstance().gameView;
        view.setCenter(view.getSize() / 2.f);
        levelLabel->setTextString("Level " + std::to_string(LevelManager::getInstance().getLevel()));
    }
}