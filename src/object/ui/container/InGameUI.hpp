//
// Created by kklt on 5/22/25.
//

#ifndef INGAMEUI_HPP
#define INGAMEUI_HPP
#include "Container.hpp"
#include "../CannonDisplay.hpp"
#include "../HealthBar.hpp"
#include "../Label.hpp"

class InGameUI: public Container {
public:
    InGameUI();

    void update(float delta) override;
    void setActive(bool state) override;

private:
    HealthBar* playerHealthBar;
    CannonDisplay* playerCannonDisplay;
    Label* goldLabel;
    Label* shipPartsLabel;
};

#endif //INGAMEUI_HPP
