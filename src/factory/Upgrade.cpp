//
// Created by kklt on 5/20/25.
//

#include "Upgrade.hpp"

#include <iostream>
#include <stdexcept>

#include "../Game.hpp"
#include "../object/ship/Ship.hpp"

const int Upgrade::MAX_LEVEL = 10;
const int Upgrade::NUM_UPGRADES = 9;
std::unordered_map<UpgradeType, std::unordered_map<int, Upgrade*>> Upgrade::upgradeMap;

Upgrade* Upgrade::getUpgrade(UpgradeType type, int level) {
    if (upgradeMap.empty()) {
        for (int i = 0; i < NUM_UPGRADES; i++) {
            new Upgrade(static_cast<UpgradeType>(i), MAX_LEVEL);
        }
        if(DEBUG) printOverallCost();
    }
    auto upgradeForType = upgradeMap[type];
    return upgradeForType[std::min(level, static_cast<int>(upgradeForType.size()))];
}

void Upgrade::printOverallCost() {
    int gold = 0;
    int parts = 0;
    for (auto& it : upgradeMap) {
        for (auto& jt : it.second) {
            gold += jt.second->getCostGold();
            parts += jt.second->getCostShipParts();
        }
    }
    std::cout << "Summed up upgrade cost:\n" << gold << " Gold\n" << parts << " ShipParts" << std::endl;
}

Upgrade::Upgrade(UpgradeType type, int level){
    if (level <= 0) {
        this->level = 1;
    }
    this->type = type;
    this->level = level;
    init();
    upgradeMap[this->type][this->level] = this;
    if (this->level > 1) {
        previous = new Upgrade(this->type, this->level - 1);
        previous->next = this;
    }
}

Upgrade* Upgrade::nextLevel() {
    return next;
}

Upgrade* Upgrade::prevLevel() {
    return previous;
}

void Upgrade::apply(Ship *ship) {
    if (previous != nullptr) {
        previous->apply(ship);
    }
    if (on_apply) on_apply(ship);
}

UpgradeType Upgrade::getType() {
    return type;
}

int Upgrade::getLevel() {
    return level;
}

std::string Upgrade::getName() {
    return name;
}

std::string Upgrade::getDescription() {
    return description;
}

int Upgrade::getCostGold() {
    return costGold;
}

int Upgrade::getCostShipParts() {
    return costShipParts;
}

void Upgrade::setMaxLevel(int maxLevel) {
    this->maxLevel = maxLevel;
    if (level > maxLevel) {
        level = maxLevel;
    }
}

void Upgrade::init() {
    switch (type) {
    case UpgradeType::HULL:
        setMaxLevel(3);
        name = "Ship Hull";
        description = "A bigger, sturdier vessel fit for a true pirate captain. Gives ye room for more cannons and sails.";
        costGold = 1200 * (level - 1) * (level-1);
        costShipParts = 15 * (level - 1);
        on_apply = [lvl = level](Ship* ship) {
            ship->hullType = lvl;
            if (lvl == 1) ship->maxHealth = 100;
            else if (lvl == 2) ship->maxHealth = 150;
            else if (lvl == 3) ship->maxHealth = 275;
            ship->velPerSailState = 28.f - 8.f * (lvl - 1);
            ship->turnPerSec = 45.f - 6.f * (lvl - 1);
        };
        break;
    case UpgradeType::HULL_STRENGTH:
        setMaxLevel(7);
        name = "Hull Strength";
        description = "Thicker planks and stronger build, so yer ship can take a beatin' and stay afloat when the cannons start flyin'.";
        costGold = 300 * (level - 1);
        costShipParts = 2 * (level - 1);
        if (level > 1) {
            on_apply = [](Ship* ship) {
                ship->maxHealth *= 1.26f;
            };
        }
        break;
    case UpgradeType::CANNONS:
        setMaxLevel(4);
        name = "Number o' Cannons";
        description = "More iron spitters along the sides! Unleash a deadly broadside and tear through enemy ships.";
        costGold = 650 * (level - 1);
        costShipParts = 6 * (level - 1);
        if (level == 1) {
            on_apply = [](Ship* ship) {
                ship->numCannons = 2;
            };
        }
        else {
            on_apply = [](Ship* ship) {
                ship->numCannons += 2;
            };
        }
        break;
    case UpgradeType::CANNON_STRENGTH:
        setMaxLevel(5);
        name = "Cannon Strength";
        description = "Upgrade to cannons that pack a wallop and blast even bigger holes in yer enemy hulls.";
        costGold = 350 * (level - 1);
        costShipParts = 0;
        if (level == 1) {
            on_apply = [](Ship* ship) {
                ship->canDamage = 33.f;
            };
        }
        else {
            on_apply = [](Ship* ship) {
                ship->canDamage *= 1.4f;
            };
        }
        break;
    case UpgradeType::CANNON_RANGE:
        setMaxLevel(4);
        name = "Cannon Range";
        description = "Let yer shots fly farther than ever. Hit 'em before they even see ye comin'.";
        costGold = 400 * (level - 1);
        costShipParts = 1 * (level - 1);
        if (level == 1) {
            on_apply = [](Ship* ship) {
                ship->canRange = 250.f;
            };
        }
        else {
            on_apply = [](Ship* ship) {
                ship->canRange *= 1.26f;
            };
        }
        break;
    case UpgradeType::CANNON_RELOADING:
        setMaxLevel(3);
        name = "Cannon Reload Time";
        description = "Train yer gunners, so ye can fire again faster and keep the pressure on.";
        costGold = 500 * (level - 1);
        costShipParts = 0;
        if (level == 1) {
            on_apply = [](Ship* ship) {
                ship->canReloadTime = 2.66f;
            };
        }
        else {
            on_apply = [](Ship* ship) {
                ship->canReloadTime *= 0.825f;
            };
        }
        break;
    case UpgradeType::SAILS:
        setMaxLevel(3);
        name = "Number o' Sails";
        description = " More canvas catchin' the wind means more speed. Raise 'em high and leave yer enemies in the spray.";
        costGold = 550 * (level - 1);
        costShipParts = 9 * (level - 1);
        if (level == 1) {
            on_apply = [](Ship* ship) {
                ship->numSails = 1;
            };
        }
        else {
            on_apply = [](Ship* ship) {
                ship->numSails += 1;
            };
        }
        break;
    case UpgradeType::SAIL_VELOCITY:
        setMaxLevel(7);
        name = "Better Sails";
        description = "Finer sails and riggin' make yer ship cut through the waves fast and fierce, just how pirates like it.";
        costGold = 300 * (level - 1);
        costShipParts = 2 * (level - 1);
        if (level > 1) {
            on_apply = [](Ship* ship) {
                ship->velPerSailState *= 1.19f;
            };
        }
        break;
    case UpgradeType::RUDER_TURN:
        setMaxLevel(5);
        name = "Maneuverability";
        description = "With a sturdier rudder, ye can turn on a dime and outmaneuver any scurvy dog that dares chase ye.";
        costGold = 250 * (level - 1);
        costShipParts = 3 * (level - 1);
        if (level > 1) {
            on_apply = [](Ship* ship) {
                ship->turnPerSec *= 1.115f;
            };
        }
        break;
    }
}
