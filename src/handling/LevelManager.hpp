//
// Created by kklt on 5/22/25.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#include "GameSaver.hpp"
#include "../Game.hpp"
#include "../factory/ShipConfiguration.hpp"
#include "../object/ship/EnemyShip.hpp"
#include "../object/ship/PlayerShip.hpp"
#include "../object/world/World.hpp"
#include "../util/RandomGenerator.hpp"

class LevelManager {
public:
    static LevelManager& getInstance();

    int getLevel();
    void addGold(int amount);
    int getGold();
    void addShipParts(int amount);
    int getShipParts();
    ShipConfiguration& getPlayerConfig();
    void nextLevel();
    void resetLevel();
    void loadGameSave(const std::string& filename = GameSaver::STANDARD_SAVEFILE);
    void saveCurrentGame(const std::string& filename = GameSaver::STANDARD_SAVEFILE);

    World* createWorld();
    PlayerShip* createPlayer(World* world);
    std::vector<EnemyShip*> createEnemiesPerIsland(Island* home);
    float determineHealAmount();

private:
    static const int START_GOLD;
    static const int START_PARTS;
    static const int LEVEL_MAX;

    RandomGenerator& rg = RandomGenerator::getInstance();
    GameSaver& gs = GameSaver::getInstance();

    int level = 1;
    int goldPlayer = START_GOLD;
    int goldPlayerLevel = 0;
    int partsPlayer = START_PARTS;
    int partsPlayerLevel = 0;
    int goldGlobal = 0;
    int goldLevel = 0;
    ShipConfiguration& playerConfig = ShipConfiguration::newDefault();

    sf::Vector2i determineMapSize(int numIslands);
    int determineIslandNumber();
    int determineEnemyNumberPerDrop();
    ShipConfiguration& determineEnemyConfig();
    float determineEnemyGoldPortion();
    int determineDropNumberPerIsland();
    int determineDropValue();

    int linearFlooredPlusProb(float start, float end);
    int logisticFlooredPlusProb(float start, float end, float growth);
    int linearPlusProb(float start, float end);
    float linearProb(float start, float end);

    static LevelManager* instance;
    LevelManager();

};

#endif //LEVELMANAGER_HPP
