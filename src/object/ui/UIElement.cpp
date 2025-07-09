//
// Created by kklt on 5/12/25.
//

#include "UIElement.hpp"

UIElement::UIElement() {
    zIndex = -1;
    relPos = sf::Vector2f(0, 0);
}

sf::Vector2f UIElement::getRelativePosition() {
    return relPos;
}

void UIElement::setRelativePosition(sf::Vector2f pos) {
    auto offset = pos - relPos;
    updatePosition(offset);
    relPos = pos;
}
