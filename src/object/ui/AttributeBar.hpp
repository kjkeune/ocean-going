//
// Created by kklt on 6/6/25.
//

#ifndef ATTRIBUTEBAR_HPP
#define ATTRIBUTEBAR_HPP
#include <functional>

#include "UIElement.hpp"

class PreviewShip;

class AttributeBar : public UIElement {
public:
    AttributeBar(sf::Vector2f size, float maxValue, std::function<float(PreviewShip*)> valueGetter);
    void startPreview(PreviewShip* ship);
    void endPreview();
    void updateCurrent(PreviewShip* ship);

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    sf::RectangleShape rect;
    sf::RectangleShape currentRect;
    sf::RectangleShape previewRect;

    float maxValue;
    std::function<float(PreviewShip*)> valueGetter;
};

#endif //ATTRIBUTEBAR_HPP
