//
// Created by kklt on 5/22/25.
//

#ifndef MAINMENUUI_HPP
#define MAINMENUUI_HPP
#include "Container.hpp"
#include "../../world/World.hpp"
#include "../button/Button.hpp"

class MainMenuUI: public Container {
public:
    static bool LEVEL_CHANGED;

    MainMenuUI();

    void update(float delta) override;
    void setActive(bool state) override;

private:
    World* backgroundWorld;
    Button* continueButton;
};

#endif //MAINMENUUI_HPP
