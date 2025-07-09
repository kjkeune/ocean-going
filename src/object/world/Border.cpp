//
// Created by kklt on 4/30/25.
//

#include "Border.hpp"

#include "../../constants/Colors.hpp"

Border::Border(sf::Vector2f pos, sf::Vector2i size)
{
    zIndex = 990;
    water.setSize(static_cast<sf::Vector2f>(size));
    water.setPosition(pos);
    water.setFillColor(colors::BORDER_OVERLAY);
};

void Border::update(float delta) {

}

void Border::render(sf::RenderTarget& target) {
    target.draw(water);
}

sf::Transformable& Border::getTrans() {
    return water;
}

void Border::onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) {

}

ConvexPolygon Border::getCollisionBounds() {
    auto bounds = rectToPoints(water.getGlobalBounds());
    return {bounds};
}
