//
// Created by kklt on 6/6/25.
//

#include "AttributeBar.hpp"

#include <utility>
#include "container/ShipPreview.hpp"
#include "../../constants/Colors.hpp"

AttributeBar::AttributeBar(sf::Vector2f size, float maxValue, std::function<float(PreviewShip *)> valueGetter) {
    this->maxValue = maxValue;
    this->valueGetter = std::move(valueGetter);
    rect.setSize(size);
    rect.setFillColor(sf::Color::Transparent);
    currentRect.setSize({0, size.y / 2.f});
    currentRect.setFillColor(colors::STATS_GREY);
    previewRect.setSize({0, size.y / 2.f});
    previewRect.setPosition({0, size.y / 2.f});
    previewRect.setFillColor(colors::STATS_GREY_LIGHT);
}

void AttributeBar::startPreview(PreviewShip *ship) {
    float currentValue = valueGetter(ship);
    float frac = currentValue / maxValue;
    previewRect.setSize({frac * getSize().x, previewRect.getSize().y});
    if (previewRect.getSize().x > currentRect.getSize().x) {
        previewRect.setFillColor(colors::MAP_SELECTED);
    }
    else if (previewRect.getSize().x < currentRect.getSize().x) {
        previewRect.setFillColor(colors::MAP_SELECTED_RED);
    }
}

void AttributeBar::endPreview() {
    previewRect.setSize({currentRect.getSize().x, previewRect.getSize().y});
    previewRect.setFillColor(colors::STATS_GREY_LIGHT);
}

void AttributeBar::updateCurrent(PreviewShip *ship) {
    float currentValue = valueGetter(ship);
    float frac = currentValue / maxValue;
    currentRect.setSize({frac * getSize().x, currentRect.getSize().y});
    previewRect.setSize({frac * getSize().x, previewRect.getSize().y});
}

void AttributeBar::update(float delta) {

}

void AttributeBar::render(sf::RenderTarget &target) {
    target.draw(rect);
    target.draw(currentRect);
    target.draw(previewRect);
}

sf::Transformable &AttributeBar::getTrans() {
    return rect;
}

sf::Vector2f AttributeBar::getSize() {
    return rect.getSize();
}

void AttributeBar::updatePosition(sf::Vector2f offset) {
    rect.move(offset);
    currentRect.move(offset);
    previewRect.move(offset);
}


