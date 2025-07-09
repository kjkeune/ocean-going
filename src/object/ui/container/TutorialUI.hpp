//
// Created by kklt on 6/17/25.
//

#ifndef TUTORIALUI_HPP
#define TUTORIALUI_HPP
#include "Container.hpp"
#include "../../world/World.hpp"

class TutorialUI: public Container {
public:
    TutorialUI();

    void setActive(bool state) override;

private:
    World* backgroundWorld;

    void initDescription(Container* container);
    void initControls(Container* container);
};

#endif //TUTORIALUI_HPP
