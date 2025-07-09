//
// Created by kklt on 5/15/25.
//

#include "CannonDisplay.hpp"
#include "../ship/Ship.hpp"

const float CannonDisplay::MARGIN = 10.f;

CannonDisplay::CannonDisplay(float height, Ship *ship) {
    this->ship = ship;
    rect.setSize(sf::Vector2f(0.f, height));
    rect.setFillColor(sf::Color::Transparent);
    if (ship != nullptr) setShip(ship);
}

void CannonDisplay::setShip(Ship *ship) {
    this->ship = ship;
    cannonRects.clear();
    auto& tex = ResourceManager::getInstance().getTexture(textures::CANNON_DISPLAY);
    auto texSize = static_cast<sf::Vector2i>(tex.getSize());
    float height = rect.getSize().y;
    float widthCannon = static_cast<float>(texSize.x) / 2 / static_cast<float>(texSize.y) * height;
    int numCannons = ship->cannonsLoaded().size() / 2;
    float width = numCannons * widthCannon + (numCannons - 1) * MARGIN;
    rect.setSize({width, height});
    for (int i = 0; i < numCannons; i++) {
        sf::RectangleShape cRect;
        cRect.setSize({widthCannon, height});
        cRect.setPosition(getRelativePosition() + sf::Vector2f{i * (widthCannon + MARGIN) - width / 2, 0});
        cRect.setTexture(&tex);
        cRect.setTextureRect(sf::IntRect({texSize.x / 2,0}, {texSize.x / 2, texSize.y}));
        cannonRects.push_back(cRect);
    }
}

void CannonDisplay::update(float delta) {
    if (ship == nullptr) {
        return;
    }
    auto texSize = static_cast<sf::Vector2i>(cannonRects[0].getTexture()->getSize());
    auto state = ship->cannonsLoaded();
    int numCannons = state.size() / 2;
    for (int i = 0; i < numCannons; i++) {
        if (state[i * 2]) {
            cannonRects[i].setTextureRect(sf::IntRect({texSize.x / 2,0}, {texSize.x / 2, texSize.y}));
        }
        else {
            cannonRects[i].setTextureRect(sf::IntRect({0,0}, {texSize.x / 2, texSize.y}));
        }
    }
}

void CannonDisplay::render(sf::RenderTarget &target) {
    target.draw(rect);
    for (auto& cRect: cannonRects) {
        target.draw(cRect);
    }
}

sf::Transformable &CannonDisplay::getTrans() {
    return rect;
}

void CannonDisplay::updatePosition(sf::Vector2f offset) {
    rect.move(offset);
    for (auto& cRect: cannonRects) {
        cRect.move(offset);
    }
}

sf::Vector2f CannonDisplay::getSize() {
    return rect.getSize();
}
