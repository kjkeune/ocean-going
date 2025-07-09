//
// Created by kklt on 5/13/25.
//

#include "Button.hpp"
#include "../../../Game.hpp"

Button::Button(sf::Vector2f size, sf::Color bg)
{
    rect.setSize(size);
    rect.setFillColor(bg);
}

Button::Button(sf::Vector2f size, sf::Texture &bg): Button(size) {
    rect.setTexture(&bg);
    rect.setTextureRect(sf::IntRect({0,0}, static_cast<sf::Vector2i>(size)));
}

Button::Button(sf::Texture &bg): Button(static_cast<sf::Vector2f>(bg.getSize()), bg) {}


void Button::setClickable(bool clickable) {
    this->clickable = clickable;
}

bool Button::isMouseOnButton() {
    return isHovered;
}

bool Button::isClickable() {
    return clickable;
}

void Button::setOnClick(std::function<void()> func) {
    on_click = std::move(func);
}

void Button::setOnHoverEnter(std::function<void()> func) {
    on_hover_enter = std::move(func);
}

void Button::setOnHoverLeave(std::function<void()> func) {
    on_hover_leave = std::move(func);
}

void Button::onClick() {
    if (on_click) on_click();
}

void Button::onHoverEnter() {
    if (on_hover_enter) on_hover_enter();
}

void Button::onHoverLeave() {
    if (on_hover_leave) on_hover_leave();
}

void Button::update(float delta) {
    auto& window = Game::getInstance().window;
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool mouseOver = rect.getGlobalBounds().contains(mousePos);
    if (mouseOver && !isHovered) {
        if (clickable) onHoverEnter();
        isHovered = true;
    }
    else if (!mouseOver && isHovered) {
        if (clickable) onHoverLeave();
        isHovered = false;
    }
}

void Button::render(sf::RenderTarget &target) {
    target.draw(rect);
}

sf::Transformable &Button::getTrans() {
    return rect;
}

void Button::setActive(bool state) {
    if (isActive() != state) {
        if (state == true) {
            EventHandler::getInstance().add(this);
        }
        else {
            EventHandler::getInstance().remove(this);
        }
    }
    GameObject::setActive(state);
}

void Button::destroy() {
    if (isActive() == true) {
        EventHandler::getInstance().remove(this);
    }
    GameObject::destroy();
}


void Button::updatePosition(sf::Vector2f offset) {
    rect.move(offset);
}

sf::Vector2f Button::getSize() {
    return rect.getSize();
}
