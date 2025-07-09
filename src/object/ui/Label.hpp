//
// Created by kklt on 5/22/25.
//

#ifndef LABEL_HPP
#define LABEL_HPP
#include "UIElement.hpp"

class Label : public UIElement {
public:
    Label(std::string text, std::string font, int fontSize, sf::Texture &icon, float maxWidth = -1);
    Label(std::string text, std::string font, int fontSize, float maxWidth = -1);
    sf::Text& getText();
    void setTextString(std::string text);
    void setOpacity(float value);
    float getOpacity();

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    static const int ICON_TEXT_MARGIN;

    sf::Text text;
    sf::RectangleShape icon;
    bool iconSet;
    float maxWidth;
    float opacity = 1.0f;
};

#endif //LABEL_HPP
