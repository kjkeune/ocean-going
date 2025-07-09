//
// Created by kklt on 5/13/25.
//

#include "SceneLoader.hpp"

#include <vector>

#include "LevelManager.hpp"
#include "ObjectManager.hpp"
#include "../object/GameObject.hpp"
#include "../Game.hpp"
#include "../object/ui/container/CompletedScreen.hpp"
#include "../object/ui/container/DeathScreen.hpp"
#include "../object/ui/container/InGameUI.hpp"
#include "../object/ui/container/MainMenuUI.hpp"
#include "../object/ui/container/ShipMenuUI.hpp"
#include "../object/ui/container/TutorialUI.hpp"

SceneLoader* SceneLoader::instance = nullptr;

SceneLoader& SceneLoader::getInstance() {
    if (instance == nullptr) {
        instance = new SceneLoader();
    }
    return *instance;
}

SceneLoader::SceneLoader() {
    sceneUIs[Scene::MAIN_MENU] = new MainMenuUI();
    sceneUIs[Scene::SHIP_MENU] = new ShipMenuUI();
    sceneUIs[Scene::TUTORIAL] = new TutorialUI();
    sceneUIs[Scene::IN_GAME] = new InGameUI();
    sceneUIs[Scene::DEATH_SCREEN] = new DeathScreen();
    sceneUIs[Scene::COMPLETED_SCREEN] = new CompletedScreen();
}

void SceneLoader::loadScene(Scene scene) {
    auto& lvlManager = LevelManager::getInstance();
    auto& game = Game::getInstance();
    game.window.setMouseCursorVisible(true);
    std::vector<GameObject*> objToRegister;
    auto& titleMusic = ResourceManager::getInstance().getMusic(sounds::TITLE_MUSIC);
    if (scene == Scene::IN_GAME) {
        // add in game objects
        World* world = lvlManager.createWorld();
        PlayerShip* player = lvlManager.createPlayer(world);
        objToRegister.push_back(world);
        objToRegister.push_back(player);
        // cursor and music
        game.window.setMouseCursorVisible(false);
        titleMusic.stop();
    }
    else if (scene == Scene::MAIN_MENU || scene == Scene::SHIP_MENU || scene == Scene::TUTORIAL) {
        if (titleMusic.getStatus() != sf::Music::Status::Playing) {
            titleMusic.play();
        }
        if (scene == Scene::MAIN_MENU) {
            titleMusic.setVolume(40);
        }
        else {
            titleMusic.setVolume(28);
        }
    }
    // switch UIs
    sceneUIs[currentScene]->setActive(false);
    objToRegister.push_back(sceneUIs[scene]);
    // clear current and add new objects
    if (scene != Scene::DEATH_SCREEN && scene != Scene::COMPLETED_SCREEN) {
        ObjectManager::getInstance().clear();
    }
    for (auto obj : objToRegister) {
        obj->setActive(true);
    }
    currentScene = scene;
}

Scene SceneLoader::getCurrentScene() {
    return currentScene;
}
