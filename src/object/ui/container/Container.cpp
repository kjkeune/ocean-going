//
// Created by kklt on 5/12/25.
//

#include "Container.hpp"

Container::Container(sf::Vector2f size, sf::Color bg) {
    rect.setSize(size);
    rect.setFillColor(bg);
}

Container::Container(sf::Vector2f size, sf::Texture &bg): Container(size) {
    rect.setTexture(&bg);
    rect.setTextureRect(sf::IntRect({0,0}, static_cast<sf::Vector2i>(bg.getSize())));
}

Container::Container(sf::Texture &bg): Container(static_cast<sf::Vector2f>(bg.getSize()), bg) {}


void Container::update(float delta) {

}

void Container::render(sf::RenderTarget &target) {
    target.draw(rect);
}

sf::Transformable &Container::getTrans() {
    return rect;
}

void Container::setActive(bool state) {
    for (auto child : elements) {
        child->setActive(state);
    }
    GameObject::setActive(state);
}

void Container::destroy() {
    for (auto child : elements) {
        child->destroy();
    }
    GameObject::destroy();
}

void Container::setBorder(float thickness, sf::Color color) {
    rect.setOutlineThickness(thickness);
    rect.setOutlineColor(color);
}

void Container::addElement(UIElement *element) {
    element->zIndex = zIndex - 10;
    if (auto c = dynamic_cast<Container*>(element)) {
        for (auto child : c->elements) {
            child->zIndex = element->zIndex - 10;
        }
    }
    element->updatePosition(rect.getPosition() - element->getTrans().getPosition() + element->getRelativePosition());
    element->setActive(isActive());
    elements.push_back(element);
}

void Container::removeAllElements() {
    for (auto element : elements) {
        element->destroy();
    }
    elements.clear();
}


void Container::updatePosition(sf::Vector2f offset) {
    rect.move(offset);
    for (auto child : elements) {
        child->updatePosition(offset);
    }
}

sf::Vector2f Container::getSize() {
    return rect.getSize();
}


