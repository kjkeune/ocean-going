//
// Created by kklt on 5/22/25.
//

#ifndef SHIPMENUUI_HPP
#define SHIPMENUUI_HPP

#include "Container.hpp"
#include "../Label.hpp"
#include "../../world/World.hpp"

class ShipMenuUI: public Container {
public:

    ShipMenuUI();

    void update(float delta) override;
    void setActive(bool state) override;

private:
    Label* goldLabel;
    Label* shipPartsLabel;
    Label* levelLabel;
    World* backgroundWorld;
};

#endif //SHIPMENUUI_HPP
