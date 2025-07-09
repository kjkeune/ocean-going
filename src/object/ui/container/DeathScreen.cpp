//
// Created by kklt on 6/10/25.
//

#include "DeathScreen.hpp"

#include "../../../constants/Colors.hpp"
#include "../../../Game.hpp"
#include "../button/PlankButton.hpp"
#include "../Label.hpp"
#include "../../../handling/LevelManager.hpp"

DeathScreen::DeathScreen():
    Container(Game::RESOLUTION, colors::HEALTH_RED_DARK_TRANS),
    sound(ResourceManager::getInstance().getSound(sounds::GAME_OVER))
{
    sound.setVolume(55);
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
    auto overL = new Label("Game Over!", fonts::TREAMD,  110);
    overL->setRelativePosition({scrSize.x / 2.f - overL->getSize().x / 2.f, levelL->getSize().y + mar + labMar});
    overL->getText().setFillColor(sf::Color::White);
    overL->getText().setStyle(sf::Text::Bold);
    addElement(overL);
    // --> Back button
    auto backB = new PlankButton();
    backB->setRelativePosition({scrSize.x / 2.f - backB->getSize().x / 2.f, scrSize.y - backB->getSize().y - mar});
    backB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::MAIN_MENU);
    });
    backB->setTextString("Back To Menu");
    this->addElement(backB);
}

void DeathScreen::setActive(bool state) {
    Container::setActive(state);
    if (state) {
        auto& lm = LevelManager::getInstance();
        int lvl = lm.getLevel();
        levelLabel->setTextString("Level " + std::to_string(lvl));
        sound.play();
    }
}
