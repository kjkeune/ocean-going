
#include "Game.hpp"

#include <iostream>

#include "util/RandomGenerator.hpp"

const sf::Vector2f Game::RESOLUTION = {1920.f, 1080.f};
const sf::Vector2f Game::VIEW_SIZE = {1365.f, 768.f};
const float Game::SOUND_MIN_DIST = VIEW_SIZE.y * 0.25f;

const double Game::NS_UPDATE = 1e9 / 60.0; // 60 updates per second
Game* Game::instance = nullptr;

Game& Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return *instance;
}

Game::Game():
    window(sf::VideoMode::getDesktopMode(), "Ocean-Going", sf::Style::Default, sf::State::Fullscreen),
    gameView({0, 0}, VIEW_SIZE),
    uiView(RESOLUTION / 2.f, RESOLUTION),
    objManager(ObjectManager::getInstance()),
    colHandler(CollisionHandler::getInstance()),
    eveHandler(EventHandler::getInstance())
{
    window.setFramerateLimit(144);
    window.setIcon(sf::Image(textures::ICON));
}

void Game::run() {
    ResourceManager::getInstance().preLoad();
    SceneLoader::getInstance().loadScene(Scene::MAIN_MENU);
    sf::Clock clock;
    sf::Clock fpsClock;
    double last = clock.getElapsedTime().asSeconds() * 1e9; // in nanoseconds
    double lag = 0.0;
    int frames = 0;
    running.store(true);
    while (running.load())
    {
        double now = clock.getElapsedTime().asSeconds() * 1e9;
        double delta = now - last;
        last = now;
        lag += delta;
        while (lag >= NS_UPDATE) {
            eveHandler.handleUserInput(window);
            update(static_cast<float>(delta * 2e-9));
            lag -= NS_UPDATE;
        }
        render();
        frames++;
        if (fpsClock.getElapsedTime().asMilliseconds() >= 1000) {
            FPS = frames;
            frames = 0;
            fpsClock.restart();
        }
    }
}

void Game::update(const float delta) {
    objManager.updateAll(delta);
    if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
        auto posPlayer = objManager.getPlayer().getTrans().getPosition();
        gameView.setCenter(posPlayer);
        sf::Listener::setPosition({posPlayer.x, 0, posPlayer.y});
    }
    colHandler.handleCollision();
}

void Game::render() {
    window.clear();
    objManager.renderAll(window, gameView, uiView);
    window.display();
}

int main() {
    Game::getInstance().run();
}