//
// Created by kklt on 5/26/25.
//

#include "PlankButton.hpp"

#include "../../../constants/Colors.hpp"

PlankButton::PlankButton():
    Button(ResourceManager::getInstance().getTexture(textures::PLANK_BUTTON)),
    text(ResourceManager::getInstance().getFont(fonts::BLACKSHIP)),
    sound(ResourceManager::getInstance().getSound(sounds::PLANK_BUTTON_HOVER))
{
    auto texSize = static_cast<sf::Vector2i>(rect.getTexture()->getSize());
    rect.setSize({static_cast<float>(texSize.x / 3), texSize.y * 1.f});
    rect.setTextureRect({{0,0}, {texSize.x / 3, texSize.y}});
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    sound.setRelativeToListener(true);
    sound.setVolume(50.f);
}

sf::Text &PlankButton::getText() {
    return text;
}

void PlankButton::setTextString(std::string text) {
    this->text.setString(text);
    this->text.setOrigin(this->text.getLocalBounds().getCenter());
    this->text.setPosition(rect.getPosition() + rect.getSize() / 2.f);
}

void PlankButton::setClickable(bool clickable) {
    Button::setClickable(clickable);
    auto texSize = static_cast<sf::Vector2i>(rect.getTexture()->getSize());
    if (clickable) {
        rect.setTextureRect({{0,0}, {texSize.x / 3, texSize.y}});
        text.setFillColor(sf::Color::White);
    }
    else {
        rect.setTextureRect({{texSize.x / 3 * 2,0}, {texSize.x / 3, texSize.y}});
        text.setFillColor(sf::Color::White);
    }
}

void PlankButton::onHoverEnter() {
    if (!clickable) {
        return;
    }
    auto texSize = static_cast<sf::Vector2i>(rect.getTexture()->getSize());
    rect.setTextureRect({{texSize.x / 3,0}, {texSize.x / 3, texSize.y}});
    if (sound.getStatus() != sf::Sound::Status::Playing) {
        sound.play();
    }
}

void PlankButton::onHoverLeave() {
    if (!clickable) {
        return;
    }
    auto texSize = static_cast<sf::Vector2i>(rect.getTexture()->getSize());
    rect.setTextureRect({{0,0}, {texSize.x / 3, texSize.y}});
}

void PlankButton::render(sf::RenderTarget &target) {
    Button::render(target);
    target.draw(text);
}


void PlankButton::updatePosition(sf::Vector2f offset) {
    Button::updatePosition(offset);
    text.move(offset);
}