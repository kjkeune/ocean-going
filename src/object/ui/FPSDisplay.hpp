//
// Created by kklt on 5/19/25.
//

#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP
#include "UIElement.hpp"

class FPSDisplay: public UIElement {
public:
    FPSDisplay();

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    sf::Text text;
};

#endif //FPSDISPLAY_HPP
