//
// Created by kklt on 6/10/25.
//

#include "GameSaver.hpp"

#include <fstream>

#include "../constants/Paths.hpp"

void to_json(json& j, const SaveData& data) {
    j = json{
        {"level", data.level},
        {"goldGlobal", data.goldGlobal},
        {"goldPlayer", data.goldPlayer},
        {"partsPlayer", data.partsPlayer}
    };
    json configJson;
    for (int i = 0; i < Upgrade::NUM_UPGRADES; i++) {
        configJson[std::to_string(i)] = data.config->getUpgrade(static_cast<UpgradeType>(i)).getLevel();
    }
    j["config"] = configJson;
}

void from_json(const json& j, SaveData& data) {
    data.level = j.at("level").get<int>();
    data.goldGlobal = j.at("goldGlobal").get<int>();
    data.goldPlayer = j.at("goldPlayer").get<int>();
    data.partsPlayer = j.at("partsPlayer").get<int>();
    const auto& configJson = j.at("config");
    data.config = &ShipConfiguration::newDefault();
    for (auto it = configJson.begin(); it != configJson.end(); ++it) {
        auto type = static_cast<UpgradeType>(std::stoi(it.key()));
        int level = it.value().get<int>();
        for (int i = 0; i < level - 1; i++) {
            if (!data.config->levelUp(type)) {
                break;
            }
        }
    }
}

const std::string GameSaver::STANDARD_SAVEFILE = "standard.json";

GameSaver* GameSaver::instance = nullptr;

GameSaver &GameSaver::getInstance() {
    if (instance == nullptr) {
        instance = new GameSaver();
    }
    return *instance;
}

bool GameSaver::saveGame(const std::string &filename, SaveData &data) {
    std::ofstream file(GAMESAVE_PATH + filename);
    if (!file) return false;
    json j = data;
    file << j.dump(4);
    return true;
}

bool GameSaver::loadGame(const std::string &filename, SaveData &data) {
    std::ifstream file(GAMESAVE_PATH + filename);
    if (!file) return false;
    json j;
    file >> j;
    data = j.get<SaveData>();
    return true;
}

