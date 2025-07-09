//
// Created by kklt on 5/22/25.
//

#include "MainMenuUI.hpp"
#include "../../../handling/LevelManager.hpp"
#include "../../../handling/SceneLoader.hpp"
#include "../../../Game.hpp"
#include "../../../constants/Colors.hpp"
#include "../button/PlankButton.hpp"

bool MainMenuUI::LEVEL_CHANGED =  false;

MainMenuUI::MainMenuUI():
    Container(Game::RESOLUTION, sf::Color::Transparent)
{
    auto scrSize = Game::RESOLUTION;
    float butMar = 30.f;
    float logoMar = 100.f;
    // init background world
    auto viewSize = static_cast<sf::Vector2i>(Game::VIEW_SIZE);
    backgroundWorld = new World({ viewSize.x  / World::TILE_SIZE + 1,  viewSize.y  / World::TILE_SIZE + 1}, {},{-10000,-10000});
    // --> logo
    auto& logoTex = ResourceManager::getInstance().getTexture(textures::LOGO);
    auto logo = new Container(static_cast<sf::Vector2f>(logoTex.getSize()) * 1.2f,logoTex);
    logo->setRelativePosition({scrSize.x * 0.5f - logo->getSize().x / 2.f ,logoMar});
    this->addElement(logo);
    // --> continue game button
    auto continueB = new PlankButton();
    continueB->setRelativePosition({scrSize.x * 0.5f - continueB->getSize().x / 2.f ,logoMar * 2 + logo->getSize().y});
    continueB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::SHIP_MENU);
    });
    continueB->setTextString("Continue Game");
    continueButton = continueB;
    this->addElement(continueB);
    // --> new game button
    auto newB = new PlankButton();
    newB->setRelativePosition({scrSize.x * 0.5f - newB->getSize().x / 2.f , logoMar * 2 + butMar + logo->getSize().y + continueB->getSize().y});
    newB->setOnClick([] {
        LevelManager::getInstance().resetLevel();
        SceneLoader::getInstance().loadScene(Scene::SHIP_MENU);
    });
    newB->setTextString("New Game");
    this->addElement(newB);
    // --> tutorial button
    auto tutB = new PlankButton();
    tutB->setRelativePosition({scrSize.x * 0.5f - tutB->getSize().x / 2.f , logoMar * 2 + butMar * 2.f + logo->getSize().y + continueB->getSize().y * 2.f});
    tutB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::TUTORIAL);
    });
    tutB->setTextString("Tutorial");
    this->addElement(tutB);
    // --> exit button
    auto exitB = new PlankButton();
    exitB->setRelativePosition({scrSize.x * 0.5f - exitB->getSize().x / 2.f ,logoMar * 2 + butMar * 3.f + logo->getSize().y + continueB->getSize().y * 3.f});
    exitB->setOnClick([] {
        Game::getInstance().running.store(false);
        Game::getInstance().window.close();
    });
    exitB->setTextString("Exit");
    this->addElement(exitB);
}

void MainMenuUI::setActive(bool state) {
    Container::setActive(state);
    backgroundWorld->setActive(state);
    if (state) {
        auto& view = Game::getInstance().gameView;
        view.setCenter(view.getSize() / 2.f);
        continueButton->setClickable(LevelManager::getInstance().getLevel() != 1);
    }
}

void MainMenuUI::update(float delta) {
    if (LEVEL_CHANGED) {
        continueButton->setClickable(LevelManager::getInstance().getLevel() != 1);
        LEVEL_CHANGED = false;
    }
}
