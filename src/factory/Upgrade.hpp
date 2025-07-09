//
// Created by kklt on 5/20/25.
//

#ifndef UPGRADE_HPP
#define UPGRADE_HPP
#include <functional>
#include <string>

class Ship;

enum class UpgradeType {
    HULL,
    HULL_STRENGTH,
    CANNONS,
    CANNON_STRENGTH,
    CANNON_RANGE,
    CANNON_RELOADING,
    SAILS,
    SAIL_VELOCITY,
    RUDER_TURN
};

class Upgrade {
public:
    const static int MAX_LEVEL;
    const static int NUM_UPGRADES;;

    static Upgrade* getUpgrade(UpgradeType type, int level);
    static void printOverallCost();

    void apply(Ship* ship);
    Upgrade* nextLevel();
    Upgrade* prevLevel();
    UpgradeType getType();
    int getLevel();
    std::string getName();
    std::string getDescription();
    int getCostGold();
    int getCostShipParts();

private:
    static std::unordered_map<UpgradeType, std::unordered_map<int, Upgrade*>> upgradeMap;

    UpgradeType type;
    int level;
    int maxLevel;
    std::string name;
    std::string description;
    int costGold;
    int costShipParts;

    Upgrade* previous = nullptr;
    Upgrade* next = nullptr;
    std::function<void(Ship*)> on_apply;

    Upgrade(UpgradeType type, int level);
    void init();
    void setMaxLevel(int maxLevel);
};

#endif //UPGRADE_HPP
