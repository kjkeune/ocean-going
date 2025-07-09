//
// Created by kklt on 5/26/25.
//

#ifndef PLANKBUTTON_HPP
#define PLANKBUTTON_HPP
#include "Button.hpp"

class PlankButton : public Button {
public:
    PlankButton();
    sf::Text& getText();
    void setTextString(std::string text);

    void render(sf::RenderTarget &target) override;

    void updatePosition(sf::Vector2f offset) override;

    void setClickable(bool clickable) override;
    void onHoverEnter() override;
    void onHoverLeave() override;

private:
    sf::Text text;
    sf::Sound sound;
};

#endif //PLANKBUTTON_HPP
