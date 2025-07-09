//
// Created by kklt on 6/10/25.
//

#ifndef COMPLETEDSCREEN_HPP
#define COMPLETEDSCREEN_HPP
#include "Container.hpp"
#include "../Label.hpp"

class CompletedScreen: public Container {
public:
    CompletedScreen();

    void setActive(bool state) override;

private:
    Label* goldLabel;
    Label* partsLabel;
    Label* levelLabel;
    sf::Sound sound;
};

#endif //COMPLETEDSCREEN_HPP
