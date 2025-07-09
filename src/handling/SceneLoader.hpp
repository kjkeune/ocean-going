//
// Created by kklt on 5/13/25.
//

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP
#include "../object/ui/container/Container.hpp"

enum class Scene {
    MAIN_MENU,
    SHIP_MENU,
    TUTORIAL,
    IN_GAME,
    DEATH_SCREEN,
    COMPLETED_SCREEN
};

class SceneLoader {
public:
    static SceneLoader& getInstance();

    void loadScene(Scene scene);
    Scene getCurrentScene();

private:
    Scene currentScene = Scene::MAIN_MENU;
    std::unordered_map<Scene, Container*> sceneUIs;

    static SceneLoader* instance;
    SceneLoader();

 };

#endif //SCENELOADER_HPP
