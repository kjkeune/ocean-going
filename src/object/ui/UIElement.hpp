//
// Created by kklt on 5/12/25.
//

#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP
#include "../GameObject.hpp"

class UIElement: public GameObject {
public:
    UIElement();
    sf::Vector2f getRelativePosition();
    void setRelativePosition(sf::Vector2f pos);
    virtual void updatePosition(sf::Vector2f offset) = 0;
    virtual sf::Vector2f getSize() = 0;

private:
    sf::Vector2f relPos;

};

#endif //UIELEMENT_HPP
