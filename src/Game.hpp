//
// Created by kklt on 4/24/25.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <atomic>

#include "handling/CollisionHandler.hpp"
#include "handling/EventHandler.hpp"
#include "handling/ObjectManager.hpp"
#include "handling/SceneLoader.hpp"

const inline bool DEBUG = true;
const inline bool PEACEFULL = false;
const inline bool RANDOM_SEED = true;
const inline unsigned int SEED = 42;

class Game {
public:
    static Game& getInstance();
    static const sf::Vector2f RESOLUTION;
    static const sf::Vector2f VIEW_SIZE;
    static const float SOUND_MIN_DIST;

    std::atomic<bool> running = false;
    int FPS = 0;
    sf::RenderWindow window;
    sf::View gameView;
    sf::View uiView;

    void run();

private:
    static const double NS_UPDATE;

    ObjectManager& objManager;
    CollisionHandler& colHandler;
    EventHandler& eveHandler;

    static Game* instance;

    Game();
    void update(float delta);
    void render();
};
#endif //GAME_H
