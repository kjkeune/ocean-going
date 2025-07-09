//
// Created by kklt on 5/28/25.
//

#ifndef MINIMAP_HPP
#define MINIMAP_HPP
#include "UIElement.hpp"
#include "../../handling/ObjectManager.hpp"

class Minimap: public UIElement {
public:
    Minimap(sf::Vector2f size);

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable &getTrans() override;
    void setActive(bool state) override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    static const float BORDER_PORTION;

    ObjectManager& objManager = ObjectManager::getInstance();
    sf::RectangleShape border;
    sf::RenderTexture staticTexture;
    sf::RenderTexture dynamicTexture;
    sf::Sprite mapSprite;
    sf::Vector2f worldSize;

    void drawStatic();
    void drawDynamic();
    sf::Vector2f getMapSize();
    sf::Vector2f worldToMinimap(sf::Vector2f pos);
};

#endif //MINIMAP_HPP
