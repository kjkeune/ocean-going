//
// Created by kklt on 6/10/25.
//

#ifndef DEATHSCREEN_HPP
#define DEATHSCREEN_HPP
#include "Container.hpp"
#include "../Label.hpp"

class DeathScreen: public Container {
public:
    DeathScreen();

    void setActive(bool state) override;

private:
    Label* levelLabel;
    sf::Sound sound;
};

#endif //DEATHSCREEN_HPP
