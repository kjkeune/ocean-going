//
// Created by kklt on 5/22/25.
//

#include "LevelManager.hpp"
#include "SceneLoader.hpp"
#include "../Game.hpp"
#include "../object/ui/container/MainMenuUI.hpp"
#include "../util/RandomGenerator.hpp"

const int LevelManager::START_GOLD = 750;
const int LevelManager::START_PARTS = 5;
const int LevelManager::LEVEL_MAX = 30;

LevelManager* LevelManager::instance = nullptr;

LevelManager& LevelManager::getInstance() {
    if (instance == nullptr) {
        instance = new LevelManager();
    }
    return *instance;
}

LevelManager::LevelManager() {
    loadGameSave();
}

World* LevelManager::createWorld() {
    int numIslands = determineIslandNumber();
    auto world = new World(determineMapSize(numIslands));
    goldLevel = 0;
    int avgDropValue = determineDropValue();
    for (int i = 0; i < numIslands; i++) {
        int drops = determineDropNumberPerIsland();
        if (world->addRandomIsland(drops, avgDropValue)) {
            goldLevel += drops;
        }
    }
    goldLevel *= avgDropValue;
    return world;
}

std::vector<EnemyShip*> LevelManager::createEnemiesPerIsland(Island* home) {
    std::vector<EnemyShip*> enemies;
    int numEnemies = determineEnemyNumberPerDrop();
    for (int i = 0; i < numEnemies; i++) {
        enemies.push_back(new EnemyShip(determineEnemyConfig(), home));
    }
    return enemies;
}

PlayerShip* LevelManager::createPlayer(World* world) {
    auto player = new PlayerShip(playerConfig);
    auto spawn = world->getSpawnPoint();
    player->getTrans().setPosition(spawn);
    player->getTrans().setRotation((static_cast<sf::Vector2f>(world->getSize()) / 2.f - spawn).angle());
    return player;
}

void LevelManager::nextLevel() {
    level++;
    goldPlayer += goldPlayerLevel;
    goldPlayerLevel = 0;
    partsPlayer += partsPlayerLevel;
    partsPlayerLevel = 0;
    goldGlobal += goldLevel;
    goldLevel = 0;
    saveCurrentGame();
}

void LevelManager::resetLevel() {
    level = 1;
    goldPlayer = START_GOLD;
    goldPlayerLevel = 0;
    partsPlayer = START_PARTS;
    partsPlayerLevel = 0;
    goldGlobal = 0;
    goldLevel = 0;
    playerConfig = ShipConfiguration::newDefault();
    saveCurrentGame();
}

void LevelManager::loadGameSave(const std::string& filename) {
    SaveData data;
    gs.loadGame(filename, data);
    level = data.level;
    goldGlobal = data.goldGlobal;
    goldPlayer = data.goldPlayer;
    partsPlayer = data.partsPlayer;
    playerConfig = *data.config;
    MainMenuUI::LEVEL_CHANGED = true;
}

void LevelManager::saveCurrentGame(const std::string& filename) {
    SaveData data;
    data.level = level;
    data.goldGlobal = goldGlobal;
    data.goldPlayer = goldPlayer;
    data.partsPlayer = partsPlayer;
    data.config = &playerConfig;
    gs.saveGame(filename, data);
}

sf::Vector2i LevelManager::determineMapSize(int numIslands) {
    int size = 2 * numIslands + 12;
    return {size,size};
}

int LevelManager::determineIslandNumber() {
    return logisticFlooredPlusProb(1.f,4.f,0.1f);
}

int LevelManager::determineDropNumberPerIsland() {
    return logisticFlooredPlusProb(1.f,5.f,0.075f);
}

int LevelManager::determineDropValue() {
    return logisticFlooredPlusProb(80.f,160.f,0.175f);
}

int LevelManager::determineEnemyNumberPerDrop() {
    return linearPlusProb(0.6f, 2.25f);
}

float LevelManager::determineEnemyGoldPortion() {
    return linearProb(0.5f,1.f);
}

ShipConfiguration &LevelManager::determineEnemyConfig() {
    int goldPerEnemy = goldGlobal * determineEnemyGoldPortion();
    ShipConfiguration& config = ShipConfiguration::newDefault();
    std::vector<UpgradeType> available;
    std::vector<UpgradeType> invalid;
    for (int i = 0; i < Upgrade::NUM_UPGRADES; i++) {
        available.push_back(static_cast<UpgradeType>(i));
    }
    while (!available.empty()) {
        int i = rg.randomInt(0, available.size() - 1);
        UpgradeType type = available[i];
        Upgrade* upgrade = config.getUpgrade(type).nextLevel();
        int cost = upgrade->getCostGold();
        if (cost > goldPerEnemy) {
            available.erase(available.begin() + i);
            continue;
        }
        // encourage small ships
        if (type == UpgradeType::HULL && rg.randomChoice(0.5f)) {
            continue;
        }
        if (!config.levelUp(type)) {
            invalid.push_back(type);
            available.erase(available.begin() + i);
            continue;
        }
        goldPerEnemy -= cost;
        if (upgrade->nextLevel() == nullptr) {
            available.erase(available.begin() + i);
        }
        available.insert(available.end(), invalid.begin(), invalid.end());
        invalid.clear();
    }
    return config;
}

float LevelManager::determineHealAmount() {
    return linearFlooredPlusProb(4.f,30.f) * 10.f;
}

int LevelManager::linearFlooredPlusProb(float start, float end) {
    float num = (end - start) / LEVEL_MAX * level + start;
    int numFloor = std::floor(num);
    float prob = num - numFloor;
    if (rg.randomChoice(prob)) {
        return numFloor + 1;
    }
    return numFloor;
}

int LevelManager::logisticFlooredPlusProb(float start, float end, float growth) {
    float num = end - (end - start) * expf(-growth * level);
    int numFloor = std::floor(num);
    float prob = num - numFloor;
    if (rg.randomChoice(prob)) {
        return numFloor + 1;
    }
    return numFloor;
}

int LevelManager::linearPlusProb(float start, float end) {
    float num = rg.randomFloat(start, (end - start) / LEVEL_MAX * level + start);
    int numFloor = std::floor(num);
    float prob = num - numFloor;
    if (rg.randomChoice(prob)) {
        return numFloor + 1;
    }
    return numFloor;
}

float LevelManager::linearProb(float start, float end) {
    return rg.randomFloat(start, (end - start) / LEVEL_MAX * level + start);
}

int LevelManager::getLevel() {
    return level;
}

int LevelManager::getGold() {
    if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
        return goldPlayerLevel;
    }
    return goldPlayer;
}

void LevelManager::addGold(int amount) {
    if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
        goldPlayerLevel += amount;
    }
    else {
        goldPlayer += amount;
    }
}

int LevelManager::getShipParts() {
    if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
        return partsPlayerLevel;
    }
    return partsPlayer;
}

void LevelManager::addShipParts(int amount) {
    if (SceneLoader::getInstance().getCurrentScene() == Scene::IN_GAME) {
        partsPlayerLevel += amount;
    }
    else {
        partsPlayer += amount;
    }
}

ShipConfiguration &LevelManager::getPlayerConfig() {
    return playerConfig;
}