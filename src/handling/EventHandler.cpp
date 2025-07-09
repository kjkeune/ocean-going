//
// Created by kklt on 5/13/25.
//

#include "EventHandler.hpp"

#include "LevelManager.hpp"
#include "../Game.hpp"

EventHandler* EventHandler::instance = nullptr;

EventHandler& EventHandler::getInstance() {
    if (instance == nullptr) {
        instance = new EventHandler();
    }
    return *instance;
}

//TODO Keybinding Map with lambda calls
void EventHandler::handleUserInput(sf::Window &window) {
    auto& objManager = ObjectManager::getInstance();
    // Handle Events
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            Game::getInstance().running.store(false);
            window.close();
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                notifyButtons();
            }
        }
        else if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
                if (keyPressed->scancode == sf::Keyboard::Scan::W) {
                    objManager.getPlayer().increaseSails();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::S) {
                    objManager.getPlayer().decreaseSails();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Space) {
                    objManager.getPlayer().fireCannons();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::I && DEBUG) {
                    objManager.getPlayer().invincible = !objManager.getPlayer().invincible;
                }
            }
            else if (SceneLoader::getInstance().getCurrentScene() == Scene::MAIN_MENU && DEBUG){
                auto& lm = LevelManager::getInstance();
                if (keyPressed->scancode == sf::Keyboard::Scan::Num1) {
                    lm.loadGameSave("level5.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num2) {
                    lm.loadGameSave("level10.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num3) {
                    lm.loadGameSave("level15.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num4) {
                    lm.loadGameSave("level20.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num5) {
                    lm.loadGameSave("level25.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num6) {
                    lm.loadGameSave("level30.json");
                }
                else if (keyPressed->scancode == sf::Keyboard::Scan::Num0) {
                    lm.loadGameSave("highroler.json");
                }
            }
        }
    }
    // Handle direct Keyboard Input
    if (SceneLoader::getInstance().getCurrentScene() != Scene::IN_GAME) {
        return;
    }
    if (isKeyPressed(sf::Keyboard::Scan::A)) {
        objManager.getPlayer().turnAngle(-1.f);
    }
    if (isKeyPressed(sf::Keyboard::Scan::D)) {
        objManager.getPlayer().turnAngle(1.f);
    }
}

void EventHandler::add(Button* observer) {
    buttonObservers.insert(observer);
}

void EventHandler::remove(Button *observer) {
    buttonObservers.erase(observer);
}

void EventHandler::notifyButtons() {
    // vector for non changing datastructure
    std::vector<Button*> observers;
    for (auto observer : buttonObservers) {
        observers.push_back(observer);
    }
    for (auto observer : observers) {
        if (observer->isMouseOnButton() && observer->isClickable()) {
            observer->onClick();
        }
    }
}
