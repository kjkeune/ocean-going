//
// Created by kklt on 4/30/25.
//

#ifndef BORDER_HPP
#define BORDER_HPP
#include "../Collidable.hpp"
#include "../GameObject.hpp"
#include "../../util/InterpolateAnimation.hpp"

class Border: public Collidable {
public:

    Border(sf::Vector2f pos, sf::Vector2i size);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;;
    void onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) override;
    ConvexPolygon getCollisionBounds() override;

private:
    sf::RectangleShape water;

};

#endif //BORDER_HPP
