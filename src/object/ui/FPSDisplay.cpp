//
// Created by kklt on 5/19/25.
//

#include "FPSDisplay.hpp"

#include "../../Game.hpp"

FPSDisplay::FPSDisplay():
    text(ResourceManager::getInstance().getFont(fonts::TUFFY))
{
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
}

void FPSDisplay::update(float delta) {
    text.setString("FPS " + std::to_string(Game::getInstance().FPS));
}

void FPSDisplay::render(sf::RenderTarget &target) {
    target.draw(text);
}

sf::Transformable &FPSDisplay::getTrans() {
    return text;
}

sf::Vector2f FPSDisplay::getSize() {
    return text.getGlobalBounds().size;
}

void FPSDisplay::updatePosition(sf::Vector2f offset) {
    text.move(offset);
}

