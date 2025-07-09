//
// Created by kklt on 5/22/25.
//

#include "Label.hpp"

#include "../../util/Text.hpp"

const int Label::ICON_TEXT_MARGIN = 5;

Label::Label(std::string text, std::string font, int fontSize, sf::Texture &icon, float maxWidth):
    text(ResourceManager::getInstance().getFont(font))
{
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Black);
    float height = fontSize;
    this->text.setPosition({height + ICON_TEXT_MARGIN, 0});
    this->icon.setSize({height, height});
    this->icon.setTexture(&icon);
    this->icon.setTextureRect(sf::IntRect({0,0}, sf::Vector2i(icon.getSize())));
    this->icon.setPosition({0, fontSize * 0.08f});
    this->maxWidth = maxWidth;
    iconSet = true;
    setTextString(text);
}

Label::Label(std::string text, std::string font, int fontSize, float maxWidth):
    text(ResourceManager::getInstance().getFont(font))
{
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Black);
    this->maxWidth = maxWidth;
    iconSet = false;
    setTextString(text);
}

void Label::update(float delta) {

}

void Label::render(sf::RenderTarget &target) {
    target.draw(icon);
    target.draw(text);
}

sf::Transformable &Label::getTrans() {
    return icon;
}

sf::Vector2f Label::getSize() {
    auto textSize = text.getGlobalBounds().size;
    if (!iconSet) {
        return textSize;
    }
    return textSize + sf::Vector2f(icon.getGlobalBounds().size.y + ICON_TEXT_MARGIN, 0);
}

void Label::updatePosition(sf::Vector2f offset) {
    text.move(offset);
    icon.move(offset);
}

void Label::setTextString(std::string text) {
    if (maxWidth == -1) {
        this->text.setString(text);
    }
    else {
        if (iconSet) {
            this->text.setString(wrapTextToWidth(text, maxWidth, this->text));
        }
        else {
            this->text.setString(wrapTextToWidth(text, maxWidth - icon.getGlobalBounds().size.y - ICON_TEXT_MARGIN, this->text));
        }
    }
}

void Label::setOpacity(float value) {
    auto alpha = static_cast<std::uint8_t>(value * 255);
    auto color = text.getFillColor();
    text.setFillColor({color.r, color.g, color.b, alpha});
    if (iconSet) {
        icon.setFillColor({255,255,255, alpha});
    }
    opacity = value;
}

float Label::getOpacity() {
    return opacity;
}

sf::Text &Label::getText() {
    return text;
}


