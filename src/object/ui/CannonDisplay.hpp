//
// Created by kklt on 5/15/25.
//

#ifndef CANNONDISPLAY_HPP
#define CANNONDISPLAY_HPP
#include "UIElement.hpp"

class Ship;

class CannonDisplay: public UIElement {
public:
    const static float MARGIN;

    CannonDisplay(float height, Ship* ship = nullptr);
    void setShip(Ship* ship);

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    Ship* ship;
    sf::RectangleShape rect;
    std::vector<sf::RectangleShape> cannonRects;
};

#endif //CANNONDISPLAY_HPP
