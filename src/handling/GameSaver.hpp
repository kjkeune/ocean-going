//
// Created by kklt on 6/10/25.
//

#ifndef GAMESAVER_HPP
#define GAMESAVER_HPP

#include "../factory/ShipConfiguration.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct SaveData {
    int level = 1;
    int goldGlobal = 0;
    int goldPlayer = 0;
    int partsPlayer = 0;
    ShipConfiguration* config = &ShipConfiguration::newDefault();
};

void to_json(json& j, const SaveData& data);
void from_json(const json& j, SaveData& data);

class GameSaver {
public:
    static const std::string STANDARD_SAVEFILE;
    static GameSaver& getInstance();

    bool saveGame(const std::string& filename, SaveData& data);
    bool loadGame(const std::string& filename, SaveData& data);

private:
    static GameSaver* instance;
    GameSaver() = default;
};

#endif //GAMESAVER_HPP
