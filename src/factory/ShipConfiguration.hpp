//
// Created by kklt on 5/20/25.
//

#ifndef SHIPCONFIGURATION_HPP
#define SHIPCONFIGURATION_HPP
#include <vector>

#include "Upgrade.hpp"

class ShipConfiguration {
public:
  	static ShipConfiguration& newDefault();
    static ShipConfiguration& newMaxedOut();
    static ShipConfiguration& newCustom();

    Upgrade& getUpgrade(UpgradeType type);
    bool levelUp(UpgradeType type);
    bool levelDown(UpgradeType type);
    void applyAll(Ship* ship);
    ShipConfiguration& copy();

private:
    std::unordered_map<UpgradeType,Upgrade*> upgrades;

    ShipConfiguration() = default;
    void add(UpgradeType type, int level);
    bool isValid();

};

#endif //SHIPCONFIGURATION_HPP
