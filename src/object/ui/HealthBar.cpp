//
// Created by kklt on 5/15/25.
//

#include "HealthBar.hpp"

#include <cmath>

#include "../../constants/Colors.hpp"
#include "../ship/Ship.hpp"


HealthBar::HealthBar(sf::Vector2f size, Ship *ship) {
    rect.setSize(size);
    rect.setFillColor(colors::HEALTH_RED_DARK_TRANS);
    rect.setOutlineThickness(size.y * 0.15f);
    rect.setOutlineColor(colors::SHIP_BROWN_DARK);
    auto& bg = ResourceManager::getInstance().getTexture(textures::HEALTH_BAR);
    healthRect.setSize(size);
    healthRect.setTexture(&bg);
    healthRect.setTextureRect(sf::IntRect({0,0}, static_cast<sf::Vector2i>(bg.getSize())));
    changeRect.setSize({0, size.y});
    changeRect.setFillColor(colors::HEALTH_RED_LIGHT);
    if (ship != nullptr) setShip(ship);
}

void HealthBar::update(float delta) {
    if (ship == nullptr) {
        return;
    }
    float shipHealth = ship->getHealth();
    auto size = rect.getSize();
    float fracHealth = shipHealth / ship->maxHealth;
    healthRect.setSize({size.x * fracHealth, size.y});
    healthRect.setPosition(rect.getPosition());
    float diffHealth = shipHealth - currentHealth;
    if (diffHealth < 0) {
        changeRect.setScale({1, 1});
        currentHealth -= changePortionPerSec * ship->maxHealth * delta;
        if (currentHealth < shipHealth) currentHealth = shipHealth;
    }
    else if (diffHealth > 0) {
        changeRect.setScale({-1, 1});
        currentHealth += changePortionPerSec * ship->maxHealth * delta;
        if (currentHealth > shipHealth) currentHealth = shipHealth;
    }
    float fracDiffHealth = std::fabs(diffHealth) / ship->maxHealth;
    changeRect.setSize({size.x * fracDiffHealth, size.y});
    changeRect.setPosition({rect.getPosition() + sf::Vector2f{healthRect.getSize().x, 0}});
}

void HealthBar::render(sf::RenderTarget &target) {
    target.draw(rect);
    target.draw(healthRect);
    target.draw(changeRect);
}

sf::Transformable &HealthBar::getTrans() {
    return rect;
}

void HealthBar::updatePosition(sf::Vector2f offset) {
    rect.move(offset);
    healthRect.move(offset);
    changeRect.move(offset);
}

sf::Vector2f HealthBar::getSize() {
    return rect.getSize();
}

void HealthBar::setShip(Ship *ship) {
    this->ship = ship;
    currentHealth = ship->getHealth();
}

