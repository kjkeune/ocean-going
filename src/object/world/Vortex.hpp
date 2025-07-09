//
// Created by kklt on 4/30/25.
//

#ifndef VORTEX_HPP
#define VORTEX_HPP
#include "../Collidable.hpp"
#include "../GameObject.hpp"

class Vortex: public Collidable {
public:
    static const float ROTATION_ANGLE_PER_SEC;

    Vortex(sf::Vector2f pos);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool state) override;

    void onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) override;
    ConvexPolygon getCollisionBounds() override;

private:
    sf::Sprite sprite;
    std::vector<sf::Vector2f> bounds;
    sf::Sound sound;

};

#endif //VORTEX_HPP
