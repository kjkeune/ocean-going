//
// Created by kklt on 5/20/25.
//

#include "ShipConfiguration.hpp"

#include <utility>

ShipConfiguration& ShipConfiguration::newDefault() {
    auto sc = new ShipConfiguration();
    for (int i = 0; i < Upgrade::NUM_UPGRADES; i++) {
        sc->add(static_cast<UpgradeType>(i), 1);
    }
    return *sc;
}

ShipConfiguration& ShipConfiguration::newMaxedOut() {
    auto sc = new ShipConfiguration();
    for (int i = 0; i < Upgrade::NUM_UPGRADES; i++) {
        sc->add(static_cast<UpgradeType>(i), Upgrade::MAX_LEVEL);
    }
    return *sc;
}

ShipConfiguration& ShipConfiguration::newCustom() {
    auto sc = new ShipConfiguration();
    sc->add(UpgradeType::HULL, 1);
    sc->add(UpgradeType::HULL_STRENGTH, 1);
    sc->add(UpgradeType::CANNONS, 2);
    sc->add(UpgradeType::CANNON_STRENGTH, 1);
    sc->add(UpgradeType::CANNON_RANGE, 1);
    sc->add(UpgradeType::CANNON_RELOADING, 1);
    sc->add(UpgradeType::SAILS, 2);
    sc->add(UpgradeType::SAIL_VELOCITY, 1);
    sc->add(UpgradeType::RUDER_TURN, 1);
    return *sc;
}

ShipConfiguration &ShipConfiguration::copy() {
    auto sc = new ShipConfiguration();
    for (auto pair : upgrades) {
        sc->add(pair.second->getType(), pair.second->getLevel());
    }
    return *sc;
}

void ShipConfiguration::applyAll(Ship *ship) {
    upgrades[UpgradeType::HULL]->apply(ship);
    for (auto [type, upgrade] : upgrades) {
        if (type == UpgradeType::HULL) {
            continue;
        }
        upgrade->apply(ship);
    }
}

Upgrade& ShipConfiguration::getUpgrade(UpgradeType type) {
    return *upgrades[type];
}

bool ShipConfiguration::levelUp(UpgradeType type) {
    auto current = upgrades[type];
    auto next = current->nextLevel();
    if (next == nullptr) {
        return false;
    }
    upgrades[type] = next;
    if (!isValid()) {
        upgrades[type] = current;
        return false;
    }
    return true;
}

bool ShipConfiguration::levelDown(UpgradeType type) {
    auto current = upgrades[type];
    auto prev = current->prevLevel();
    if (prev == nullptr) {
        return false;
    }
    upgrades[type] = prev;
    if (!isValid()) {
        upgrades[type] = current;
        return false;
    }
    return true;
}

void ShipConfiguration::add(UpgradeType type, int level) {
    upgrades[type] = Upgrade::getUpgrade(type, level);
}

bool ShipConfiguration::isValid() {
    if (upgrades[UpgradeType::HULL]->getLevel() == 1) {
        return upgrades[UpgradeType::CANNONS]->getLevel() == 1 && upgrades[UpgradeType::SAILS]->getLevel() == 1;
    }
    if (upgrades[UpgradeType::HULL]->getLevel() == 2) {
        return upgrades[UpgradeType::CANNONS]->getLevel() <= 2 && upgrades[UpgradeType::SAILS]->getLevel() <= 2;
    }
    if (upgrades[UpgradeType::HULL]->getLevel() == 3) {
        return upgrades[UpgradeType::CANNONS]->getLevel() <= 4 && upgrades[UpgradeType::SAILS]->getLevel() <= 3;
    }
    return false;
}


