//
// Created by kklt on 5/15/25.
//

#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP
#include "UIElement.hpp"
#include "SFML/System/Vector2.hpp"

class Ship;

class HealthBar: public UIElement {
public:
    float changePortionPerSec = 0.4f;

    HealthBar(sf::Vector2f size, Ship* ship = nullptr);
    void setShip(Ship* ship);

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    Ship* ship = nullptr;
    sf::RectangleShape rect;
    sf::RectangleShape healthRect;
    sf::RectangleShape changeRect;
    float currentHealth;

};

#endif //HEALTHBAR_HPP
